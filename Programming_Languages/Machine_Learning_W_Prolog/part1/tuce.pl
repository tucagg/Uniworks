% Teslimat personeli
% personel(ID, weighthcapacity, totaltime, is, location)
personel(1, 16, 12, dolu, admin_office).
personel(2, 20, 8, no_job, engineering_build).
personel(3, 24, 20, no_job, lecture_hall_a).

% Yerler
yer(admin_office).
yer(engineering_build).
yer(lecture_hall_a).
yer(cafeteria).
yer(library).   
yer(instute_y).
yer(social_science_bld).
yer(instute_x).

% Nesneler
% nesne(ID, weight, from, to, priority, carryingpersonID)
nesne(1, 5, admin_office, engineering_build, medium, 1).
nesne(2, 8, engineering_build, lecture_hall_a, medium, no_person).
nesne(3, 3, lecture_hall_a, admin_office, high, no_person).
nesne(4, 6, admin_office, lecture_hall_a, low, no_person).
nesne(5, 10, engineering_build, admin_office, medium, no_person).

% Harita
kenar(admin_office, engineering_build, 3).
kenar(engineering_build, admin_office, 3). 
kenar(engineering_build, lecture_hall_a, 2).
kenar(lecture_hall_a, engineering_build, 2). 
kenar(admin_office, cafeteria, 4).
kenar(cafeteria, admin_office, 4). 
kenar(admin_office, library, 1).
kenar(library, admin_office, 1).
kenar(engineering_build, library, 5).
kenar(library, engineering_build, 5). 
kenar(library, instute_y, 3).
kenar(instute_y, library, 3). 
kenar(lecture_hall_a, instute_y, 3).
kenar(instute_y, lecture_hall_a, 3). 
kenar(cafeteria, library, 5).
kenar(library, cafeteria, 5). 
kenar(library, social_science_bld, 2).
kenar(social_science_bld, library, 2). 
kenar(cafeteria, social_science_bld, 2).
kenar(social_science_bld, cafeteria, 2). 
kenar(social_science_bld, instute_x, 8).
kenar(instute_x, social_science_bld, 8). 


% Dijkstra Algoritması
en_kisa_yol(Start, End, Distance, Path) :-
    setof([D, P], yol(Start, End, D, P), Paths),
    Paths = [_ | _], % Paths boş değilse devam et
    en_kisa_path(Paths, [Distance, Path]).

en_kisa_path([[Distance, Path] | RestPaths], Shortest) :-
    en_kisa_path(RestPaths, [RestDistance, _]),
    ( Distance < RestDistance ->
        Shortest = [Distance, Path]
    ; Shortest = [RestDistance, _]
    ).

en_kisa_path([], [inf, []]).

% Yolu Bulma
yol(Start, End, Distance, Path) :-
    yol(Start, End, [Start], Distance, Path).

yol(End, End, _, 0, []).

yol(Start, End, Visited, Distance, [_ | Path]) :-
    kenar(Start, Next, EdgeLength),
    \+ member(Next, Visited),
    yol(Next, End, [Next | Visited], RestDistance, Path),
    Distance is EdgeLength + RestDistance.


calismayan_personeller(PersonelID) :-
    personel(PersonelID, _, _, no_job, _).

%su anda tasinan nesneler
suanda_tasinan_nesneler(NesneID) :-
    nesne(NesneID, _, _, _, _, PersonelID),
    personel(PersonelID, _, _, _, _),
    write('Nesne: '), write(NesneID), write(' Personel: '), write(PersonelID), nl.
    

tasınacak_nesneler(NesneID) :-
    nesne(NesneID, _, _, _, _, no_person).


personel_tasiyabilir_mi(PersonelID, NesneID) :-
    personel(PersonelID, WeightCapacity, _, _, _),
    nesne(NesneID, Weight, _, _, _, _),
    Weight =< WeightCapacity.

%su anda tasinan nesneler
acil_suanda_tasinan_nesneler(Tasinan) :-
    nesne(Tasinan, _, _, _, _, PersonelID),
    personel(PersonelID, _, _, _, _).

% Nesnenin teslimatı kim tarafından ne kadar sürede yapılacak
% personel şu anda taşımadaysa ama elindeki nesnenin aciliyeti sorgulanan nesneden daha düşükse o personele de süre hesaplattırıyorum
kim_kac_sure(NesneID):-
    (   personel(Tasiyan, _, _, dolu, _),
        acil_suanda_tasinan_nesneler(Tasinan),
        aciliyet(NesneID, Tasinan, Acilolan),
        Tasinan \= Acilolan,
        personel_tasiyabilir_mi(Tasiyan, NesneID),
        personel(Tasiyan, _, TotalTime, _, From),
        nesne(NesneID, _, To, Gid, _, _),
        en_kisa_yol(From, To, Distance, _),
        en_kisa_yol(To, Gid, Distance2, _),
        Distance3 is Distance + Distance2,
        TotalTime >= Distance3,
        write('Nesne: '), write(NesneID), write(' Personel: '), write(Tasiyan), write(' Süre: '), write(Distance3), nl
    ;   calismayan_personeller(PersonelID),
        personel_tasiyabilir_mi(PersonelID, NesneID),
        personel(PersonelID, _, TotalTime, _, From),
        nesne(NesneID, _, To, Gid, _, _),
        en_kisa_yol(From, To, Distance, _),
        en_kisa_yol(To, Gid, Distance2, _),
        Distance3 is Distance + Distance2,
        TotalTime >= Distance3,
        write('Nesne: '), write(NesneID), write(' Personel: '), write(PersonelID), write(' Süre: '), write(Distance3), nl
    ).

% Öncelikleri sayısal değerlere atama
sayisal_ozellik(high, 3).
sayisal_ozellik(medium, 2).
sayisal_ozellik(low, 1).

% Sayısal büyüklük sıralamasını kontrol etme
buyukluk_siralamasi(X, Y) :- sayisal_ozellik(X, XValue), sayisal_ozellik(Y, YValue), XValue > YValue.

% Nesnelerin önceliklerini kontrol edip öncelikli olanı bulma
aciliyet(NesneID, NesneID2, Acilolan) :-
    nesne(NesneID, _, _, _, Priority, _),
    nesne(NesneID2, _, _, _, Priority2, _),
    buyukluk_siralamasi(Priority, Priority2),
    Acilolan = NesneID.

nesne_durumu(NesneID) :-
    suanda_tasinan_nesneler(NesneID);
    tasınacak_nesneler(NesneID),
    findall(_, kim_kac_sure(NesneID), _).
    



?- nesne_durumu(1).
