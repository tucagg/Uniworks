(load "tucepolat_yancar.lisp")


(setq exitlo 0)
(setq error 0)

(defparameter values(list))

(defun tucepolat ()
    (loop
        
        (setq list1 (list)) 
        (setq list2 (list)) 
        
        (tucepolat_yancar list1 list2)
        (setq list1 (reverse list1))
        (setq list2 (reverse list2))
        
        (listdonus list1 list2)

        (if (explistbul list1)
            (progn
                (if (equal error 0)
                    (progn
                        (setq result (expuret list1 list2))
                        (if (not (equal result nil))
                            (progn
                                (format t "~A" result)
                            )
                        )
                        (setq error 0)
                    )
                    (return)
                )
                (write-line "")
            )
            
            (if (fonk_bul list1)
                (if (equal error 0)
                    (progn
                        (setq error 0)
                    )
                    (return)
                )
                (progn
                    (write-line "SYNTAX_ERROR")
                )
            )
            
        )
        
        

        (if (equal exitlo 1)
            (progn
                (setq exitlo 0)
                (return)
            )
        ) 
    )
)


(defun explistbul (list1)
    (or
        (and
            (equal (length list1) 1)
            (expdonustur_hizmetci (list (nth 0 list1)))
        )
        (and
            (equal (length list1) 2)
            (expdonustur_hizmetci (nth 0 list1))
            (expdonustur_hizmetci (nth 1 list1))
        )
        (and
            (equal (length list1) 3)
            (expdonustur_hizmetci (nth 0 list1))
            (expdonustur_hizmetci (nth 1 list1))
            (expdonustur_hizmetci (nth 2 list1))
        )
        (and
            (equal (length list1) 4)
            (expdonustur_hizmetci (nth 0 list1))
            (expdonustur_hizmetci (nth 1 list1))
            (expdonustur_hizmetci (nth 2 list1))
            (expdonustur_hizmetci (nth 3 list1))
        )
        (and
            (equal (length list1) 5)
            (expdonustur_hizmetci (nth 0 list1))
            (expdonustur_hizmetci (nth 1 list1))
            (expdonustur_hizmetci (nth 2 list1))
            (expdonustur_hizmetci (nth 3 list1))
            (expdonustur_hizmetci (nth 4 list1))
        )
        (and
            (equal (length list1) 6)
            (expdonustur_hizmetci (nth 0 list1))
            (expdonustur_hizmetci (nth 1 list1))
            (expdonustur_hizmetci (nth 2 list1))
            (expdonustur_hizmetci (nth 3 list1))
            (expdonustur_hizmetci (nth 4 list1))
            (expdonustur_hizmetci (nth 5 list1))
        )
        (expbul list1)
    )
)

(defun idbul (list1)
    (or 
        (and
            (equal (length list1)1)
            (string= (nth 0 list1) "ID")
        )
        (and
            (equal (length list1)2)
            (string= (nth 0 list1) "ID")
            (string= (nth 1 list1) "ID")
        )
        (and
            (equal (length list1)3)
            (string= (nth 0 list1) "ID")
            (string= (nth 1 list1) "ID")
            (string= (nth 2 list1) "ID")
        )
    )
)

;BU UCLU OLARAK GIRILDIGINDE HATA VERDIREN FONK.
(defun fonk_bul (list1)
    (or 
        (and 
            (equal (length list1) 3)
            (string= (nth 0 list1) "KW_DEF")
            (string= (nth 1 list1) "ID")
            (explistbul (nth 2 list1))
        )
        (and 
            (equal (length list1) 4)
            (string= (nth 0 list1) "KW_DEF")
            (string= (nth 1 list1) "ID")
            (idbul  (nth 2 list1))
            (explistbul (nth 3 list1))
        )
    )
)

;FONK TANIMLAMA YARDIM
(defun expdonustur_hizmetci  (x)
    (if (equal (stringp x) t)
        (return-from expdonustur_hizmetci (expbul (list x))) 
    )
    (if (not (equal (stringp x) t))
        (return-from expdonustur_hizmetci (expbul x))
    )
)


(defun listdonus ('list1 'list2)

    (setq listParser (list))  
    (setq tempList (list))    
    (setq tempList0 (list))   
    (setq tempList00 (list))  
    
    (setq listParser2 (list)) 
    (setq tempList2 (list))   
    (setq tempList3 (list))   
    (setq tempList4 (list))   
    
    (setq c  0)
    (setq c2 0)
    (setq c3 0)

    (setq c4 0)
    (setq c5 0)
    (setq c6 0)


    (if (string= (nth 0 list1) "OP_OP")
        
        (loop for x in (cdr list1)
            do
            (if (and (not (string= x "OP_OP"))(not (string= x "OP_CP"))(equal c 0)(equal c2 0))
                (setq listParser(cons x listParser))
                (if (and (not (string= x "OP_OP"))(not (string= x "OP_CP"))(equal c 1)(equal c2 0))
                    (setq tempList (cons x tempList))
                    (if (and (not (string= x "OP_OP"))(not (string= x "OP_CP"))(equal c2 1)(equal c3 0))
                        (setq tempList0 (cons x tempList0))
                        (if (and (not (string= x "OP_OP"))(not (string= x "OP_CP"))(equal c3 1))
                            (setq tempList00 (cons x tempList00))
                        )
                    )
                )
            )
            (if (and (string= x "OP_OP")(equal c2 1))
                (setq c3 1)
                (if (and (string= x "OP_OP")(equal c 1))
                    (setq c2 1)
                    (if (and (string= x "OP_OP")(equal c 0))
                        (setq c 1)
                    )
                )
            )
            (if (and (string= x "OP_CP")(equal c2 0)(equal c 1))
            (progn
                (if (equal c 1)
                    (progn
                        (setq tempList (reverse tempList))
                        (setq listParser (push tempList listParser))
                        (setq tempList (list))
                    )
                )
                (setq c 0)
            )
            (progn
                (if (and (string= x "OP_CP")(equal c2 1)(equal c3 0))
                    (progn
                        (if (equal c 1)
                            (progn
                                (setq tempList0 (reverse tempList0))
                                (setq tempList (push tempList0 tempList))
                                (setq tempList0 (list))
                            )
                        )
                        (setq c2 0)
                    )
                    (progn
                        (if (and (string= x "OP_CP")(equal c3 1))
                        (progn
                            (if (equal c 1)
                                (progn
                                    (setq tempList00 (reverse tempList00))
                                    (setq tempList0 (push tempList00 tempList0))
                                    (setq tempList00 (list))
                                )
                            )
                            (setq c3 0)
                        )
                        )
                    )
                )
            )
            ) 
        )
    )
    (if (string= (nth 0 list2) "(")
        
        (loop for x in (cdr list2)
            do
            (if (and (not (string= x "("))(not (string= x ")"))(equal c4 0)(equal c5 0))
                (setq listParser2(cons x listParser2))
            )
            (if (and (not (string= x "("))(not (string= x ")"))(equal c4 1)(equal c5 0))
                (setq tempList2 (cons x tempList2))
            )
            (if (and (not (string= x "("))(not (string= x ")"))(equal c5 1)(equal c6 0))
                (setq tempList3 (cons x tempList3))
            )
            (if (and (not (string= x "("))(not (string= x ")"))(equal c6 1))
                (setq tempList4 (cons x tempList4))
            )
            (if (and (string= x "(")(equal c5 1))
                    (setq c6 1)
            )
            (if (and (string= x "(")(equal c4 1))
                    (setq c5 1)
            )
            (if (and (string= x "(")(equal c4 0))
                    (setq c4 1)
            )

            (if (and (string= x ")")(equal c5 0)(equal c4 1))
            (progn
                (if (equal c4 1)
                    (progn
                        (setq tempList2 (reverse tempList2))
                        (setq listParser2 (push tempList2 listParser2))
                        (setq tempList2 (list))
                    )
                )
                (setq c4 0)
            )
            ) 
            (if (and (string= x ")")(equal c5 1)(equal c6 0))
            (progn
                (if (equal c4 1)
                    (progn
                        (setq tempList3 (reverse tempList3))
                        (setq tempList2 (push tempList3 tempList2))
                        (setq tempList3 (list))
                    )
                )
                (setq c5 0)
            )
            ) 
            (if (and (string= x ")")(equal c6 1))
            (progn
                (if (equal c4 1)
                    (progn
                        (setq tempList4 (reverse tempList4))
                        (setq tempList3 (push tempList4 tempList3))
                        (setq tempList4 (list))
                    )
                )
                (setq c6 0)
            )
            )
        )
    )
    (setq listParser (reverse listParser))
    (setq listParser2 (reverse listParser2))
    (setq list1 listParser)
    (setq list2 listParser2)
)
(defun expuret (list1 list2)
    (if (string= (nth 0 list1)  "KW_EXIT")
        (progn
            (setq exitlo 1)
            (return-from expuret nil)
        )
    )
    (if (string= (nth 0 list1)  "OP_PLUS")
        (let ((temp1)(temp2)(temp3)(temp4)(rtn))
            (if (equal (stringp (nth 1 list1)) t )
                (if (string= (nth 1 list1) "VALUEF")
                    (setq temp1 (kesirdonus (nth 1 list2)))
                    (progn
                        (if (string= (nth 1 list1) "ID")
                            (progn
                                (setq index (searchList (nth 1 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp1 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp1 (kesirdonus (expuret (nth 1 list1)(nth 1 list2))))
            )
            (if (equal (stringp (nth 2 list1)) t )
                (if (string= (nth 2 list1) "VALUEF")
                    (setq temp2 (kesirdonus (nth 2 list2)))
                    (progn
                        (if (string= (nth 2 list1) "ID")
                            (progn
                                (setq index (searchList (nth 2 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp2 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp2 (kesirdonus (expuret (nth 2 list1)(nth 2 list2))))
            )  
            (if (equal error 0)
                (progn
                    (setq temp3 (+ (* (parse-integer (nth 0 temp1))(parse-integer (nth 1 temp2)))(* (parse-integer (nth 0 temp2))(parse-integer (nth 1 temp1)))))
                    (setq temp4 (* (parse-integer (nth 1 temp1))(parse-integer (nth 1 temp2))))
                    (setq temp3 (write-to-string temp3))
                    (setq temp4 (write-to-string temp4))
                    (return-from expuret (concatenate 'string temp3 "f" temp4))
                )
                (return-from expuret "error")
            )
        )
    )
    (if (string= (nth 0 list1)  "OP_MINUS")
        (let ((temp1)(temp2)(temp3)(temp4)(rtn))
            (if (equal (stringp (nth 1 list1)) t )
                (if (string= (nth 1 list1) "VALUEF")
                    (setq temp1 (kesirdonus (nth 1 list2)))
                    (progn
                        (if (string= (nth 1 list1) "ID")
                            (progn
                                (setq index (searchList (nth 1 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp1 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp1 (kesirdonus (expuret (nth 1 list1)(nth 1 list2))))
            )
            (if (equal (stringp (nth 2 list1)) t )
                (if (string= (nth 2 list1) "VALUEF")
                    (setq temp2 (kesirdonus (nth 2 list2)))
                    (progn
                        (if (string= (nth 2 list1) "ID")
                            (progn
                                (setq index (searchList (nth 2 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp2 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    ) 
                )
                (setq temp2 (kesirdonus (expuret (nth 2 list1)(nth 2 list2))))
            )  
            (if (equal error 0)
                (progn
                    (setq temp3 (- (* (parse-integer (nth 0 temp1))(parse-integer (nth 1 temp2)))(* (parse-integer (nth 0 temp2))(parse-integer (nth 1 temp1)))))
                    (setq temp4 (* (parse-integer (nth 1 temp1))(parse-integer (nth 1 temp2))))
                    (setq temp3 (write-to-string temp3))
                    (setq temp4 (write-to-string temp4))
                    (return-from expuret (concatenate 'string temp3 "f" temp4))
                )
                (return-from expuret "error")
            )
        )    
    )               
    (if (string= (nth 0 list1)  "OP_MULT")
        (let ((temp1)(temp2)(temp3)(temp4)(rtn))
            (if (equal (stringp (nth 1 list1)) t )
                (if (string= (nth 1 list1) "VALUEF")
                    (setq temp1 (kesirdonus (nth 1 list2)))
                    (progn
                        (if (string= (nth 1 list1) "ID")
                            (progn
                                (setq index (searchList (nth 1 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp1 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp1 (kesirdonus (expuret (nth 1 list1)(nth 1 list2))))
            )
            (if (equal (stringp (nth 2 list1)) t )
                (if (string= (nth 2 list1) "VALUEF")
                    (setq temp2 (kesirdonus (nth 2 list2)))
                    (progn
                        (if (string= (nth 2 list1) "ID")
                            (progn
                                (setq index (searchList (nth 2 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp2 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp2 (kesirdonus (expuret (nth 2 list1)(nth 2 list2))))
            )  
            (if (equal error 0)
                (progn
                    (setq temp3 (* (parse-integer (nth 0 temp1))(parse-integer (nth 0 temp2))))
                    (setq temp4 (* (parse-integer (nth 1 temp1))(parse-integer (nth 1 temp2))))
                    (setq temp3 (write-to-string temp3))
                    (setq temp4 (write-to-string temp4))
                    (return-from expuret (concatenate 'string temp3 "f" temp4))
                )
                (return-from expuret "error")
            )
        )
    )
    (if (string= (nth 0 list1)  "OP_DIV")
        (let ((temp1)(temp2)(temp3)(temp4)(rtn))
            (if (equal (stringp (nth 1 list1)) t )
                (if (string= (nth 1 list1) "VALUEF")
                    (setq temp1 (kesirdonus (nth 1 list2)))
                    (progn
                        (if (string= (nth 1 list1) "ID")
                            (progn
                                (setq index (searchList (nth 1 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp1 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp1 (kesirdonus (expuret (nth 1 list1)(nth 1 list2))))
            )
            (if (equal (stringp (nth 2 list1)) t )
                (if (string= (nth 2 list1) "VALUEF")
                    (setq temp2 (kesirdonus (nth 2 list2)))
                    (progn
                        (if (string= (nth 2 list1) "ID")
                            (progn
                                (setq index (searchList (nth 2 list2) variables))
                                (if (not (equal index nil))
                                    (progn
                                        (setq temp2 (kesirdonus (nth index values)))
                                    )
                                )
                            )
                            (progn
                                (setq error 1)
                                (return)
                            )
                        )
                    )
                )
                (setq temp2 (kesirdonus (expuret (nth 2 list1)(nth 2 list2))))
            )  
            (if (equal error 0)
                (progn
                    (setq temp3 (* (parse-integer (nth 0 temp1))(parse-integer (nth 1 temp2))))
                    (setq temp4 (* (parse-integer (nth 1 temp1))(parse-integer (nth 0 temp2))))
                    (setq temp3 (write-to-string temp3))
                    (setq temp4 (write-to-string temp4))
                    (return-from expuret (concatenate 'string temp3 "f" temp4))
                )
                (return-from expuret "error")
            )
        )
    )
    (if (string= (nth 0 list1)  "VALUEF")
        (return-from expuret (nth 0 list2))
    )
    
)
(defun kesirdonus (f)
    (let ((temp "") (i 0)(temp1)(temp2))
        (loop   
            (when (string= (subseq f i (+ 1 i)) "f") 
                (return)
            )
            (if (and (not (string= (subseq f i (+ 1 i)) ")"))(not (string= (subseq f i (+ 1 i)) "(")))
                (setq temp (concatenate 'string temp (subseq f i (+ 1 i))))
            )
            (setq i (+ 1 i))
        )
        (setq temp1 temp)
        (setq temp (list))
        (setq i (+ 1 i))
        (loop
            (when (equal (length f) i) 
                (return)
            )
            (if (and (not (string= (subseq f i (+ 1 i)) ")"))(not (string= (subseq f i (+ 1 i)) "(")))
                (setq temp (concatenate 'string temp (subseq f i (+ 1 i))))
            )
            (setq i (+ 1 i))
        )
        (setq temp2 temp)
        (return-from kesirdonus (list temp1 temp2))
    )
)
(defun expbul(list1)
    (or 
        (and
            (equal (length list1) 1)
            (string= (nth 0 list1) "KW_EXIT")
        )
        (and
            (equal (length list1) 1)
            (string= (nth 0 list1) "ID")
        )
        (and
            (equal (length list1) 1)
            (string= (nth 0 list1) "VALUEF")
        )
        (and 
            (equal (length list1) 2)
            (string= (nth 0 list1)  "ID")
            (explistbul (nth 1 list1))
        )
        (and 
            (equal (length list1) 3)
            (string= (nth 0 list1)  "ID")
            (explistbul (nth 1 list1))
        )
        (and 
            (equal (length list1) 4)
            (string= (nth 0 list1)  "ID")
            (explistbul (nth 1 list1))
        )
        (and 
            (equal (length list1) 3)
            (string= (nth 0 list1)  "OP_PLUS")
            (expdonustur_hizmetci (nth 1 list1)) (expdonustur_hizmetci (nth 2 list1))
        )
        (and 
            (equal (length list1) 3)
            (string= (nth 0 list1) "OP_MINUS")
            (expdonustur_hizmetci (nth 1 list1))(expdonustur_hizmetci (nth 2 list1))
        )
        (and
            (equal (length list1) 3)
            (string= (nth 0 list1) "OP_MULT")
            (expdonustur_hizmetci (nth 1 list1))(expdonustur_hizmetci (nth 2 list1))
        )
        (and
            (equal (length list1) 3)
            (string= (nth 0 list1) "OP_DIV")
            (expdonustur_hizmetci (nth 1 list1))(expdonustur_hizmetci (nth 2 list1))
        )

    )
) 

(tucepolat)