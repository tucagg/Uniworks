classify1(SepalLength, SepalWidth, PetalLength, PetalWidth, ClassLabel) :-
    (
        PetalLength =< 2.45, !, ClassLabel = setosa;
        PetalLength > 2.45,
        (
            PetalWidth =< 1.75,
            (
                PetalLength =< 4.95,
                (
                    PetalWidth =< 1.65, !, ClassLabel = versicolor;
                    PetalWidth > 1.65, !, ClassLabel = virginica
                );
                PetalLength > 4.95,
                (
                    PetalWidth =< 1.55, !, ClassLabel = virginica;
                    PetalWidth > 1.55,
                    (
                        SepalLength =< 6.95, !, ClassLabel = versicolor;
                        SepalLength > 6.95, !, ClassLabel = virginica
                    )
                )
            );
            PetalWidth > 1.75,
            (
                PetalLength =< 4.85,
                (
                    SepalWidth =< 3.10, !, ClassLabel = virginica;
                    SepalWidth > 3.10, !, ClassLabel = versicolor
                );
                PetalLength > 4.85, !, ClassLabel = virginica
            )
        )
    ).



classify(SepalLength, SepalWidth, PetalLength, PetalWidth):-
    classify1(SepalLength, SepalWidth, PetalLength, PetalWidth, ClassLabel),
    write('Yes with class label: '), write(ClassLabel), nl.


?- classify(4.9,2.4,3.3,1.0).
