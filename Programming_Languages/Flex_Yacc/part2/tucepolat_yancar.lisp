(setq hatasebebi (list "(" ")" "\""))
(setq op_c 0)
(setq exit1 0)
(setq exit2 0)


(setq keywords (list "and" "or" "not" "eq" "less" "nil" "list" "set" "append" "concat" "def" "for" "if" "exit" "load" "display" "true" "false"))

(setq kw (list "KW_AND" "KW_OR" "KW_NOT" "KW_EQUAL" "KW_LESS" "KW_NIL" "KW_LIST" "KW_SET" "KW_APPEND" "KW_CONCAT" "KW_DEF" "KW_FOR" "KW_IF" "KW_EXIT" "KW_LOAD" "KW_DISPLAY" "KW_TRUE" "KW_FALSE"))

(setq operators (list "+" "-" "/" "**" "*" "(" ")" "\"" ","))

(setq op (list "OP_PLUS" "OP_MINUS" "OP_DIV" "OP_DBLMULT" "OP_MULT" "OP_OP" "OP_CP" "OP_OC" "OP_CC" "OP_COMMA"))

(setq comment ";")


(defun tucepolat_yancar(list1 list2)

        (defparameter str (read-line)) 
        (let 
            ((words (list)))
            (setq words (bolucu str))
            (loop for word in words
			    do
                (if (string= word "exit")
                    (progn
                        (setq exit1 1)
                        (return)
                    )
                )
                (if (equal (kelime_bak word list1 list2) 2)
                    (progn 
                        (return)    
                    )
		        )  
                     
            )
        )          
)


(defun opkontrol (x x2 'list1 'list2)
    (setq son (pulsar x2 operators))
    (if (not (equal son nil))
        (progn
            (if (equal son 7) 
                (progn 
                    (if (equal op_c 0)
                        (progn
                            (setq op_c 1)
                        )
                        (progn
                            (setq op_c 0)
                        )
                    )
                    (setq son (+ son (mod op_c 2))) 
                )
            )
            (setq list1 (cons (nth son op) list1))
            (setq list2 (cons x2 list2))
        )
    )
    son
)

(defun kwkontrol (x x2 i len 'list1 'list2)
    (setq son nil)
    (setq index (pulsar x2 keywords))
    (if (not (equal index nil)) 
        (if (>= i len)
            (progn
                (setq list1 (cons (nth index kw) list1))
                (setq list2 (cons x2 list2))
                (setq son 0)
            )
            (progn
                (setq temp (subseq x i (+ i 1)))
                (if (equal (pulsar temp hatasebebi) nil)
                    (if (equal (identifier_control_helper (concatenate 'string x2 temp)) nil)
                        (progn
                            (format t "SYNTAX_ERROR ~S can not be tokenized.~%" (subseq x2 j len))
                            (setq exit2 -1)
                        )
                    )
                    (progn
                        (setq list1 (cons (nth index kw) list1))
                        (setq list2 (cons x2 list2))
                        (setq son 1)                     
                    )
                )
            )        
        )        
    )
    son
)

(defun valbak (x x2 i j len 'list1 'list2)
    (setq son nil)
    (setq index (hizmetci_val x2))

    (if (not (equal index nil))
            (progn
                (loop
                    (setq i (+ i 1))
                    (when (or (equal (hizmetci_val (subseq x j (- i 1))) nil) (> i len)) 
                    (return))
                )
                (setq i (- i 1))
                (if (equal (hizmetci_val (subseq x j i)) nil) 
                    (progn
                        (setq i (- i 1))
                        (if (equal (pulsar (subseq x i (+ i 1)) hatasebebi) nil)
                            (progn
                                (if (string= (subseq x i (+ i 1)) "f")
                                    (progn
                                        (setq list1 (cons '"VALUEF" list1))
                                        (setq temp x)
                                        (setq i2 0)

                                        (loop for i from 0 to (length x)
                                            do
                                            (if (string= (subseq temp 0 1) "(")
                                                (setq temp (subseq temp 1))
                                            )
                                        )
                                        
                                        (loop for i from 0 to (length x)
                                            do
                                            (if (string= (subseq (reverse temp) 0 1) ")")
                                                (setq temp (reverse (subseq (reverse temp) 1)))
                                            )
                                        )

                                        (setq list2(cons temp list2))
                                        (loop 
                                            (if (or (equal (subseq temp i) "") (equal (subseq temp i) ")")) (return))
                                            (setq i (+ i 1))
                                        )
                                    )
                                )
                            )
                            (progn
                                (setq exit2 -1)
                            )
                        )
                    )
                    (progn
                        (setq exit2 -1)
                    )
                )	
                (setq son i)							     
            )	
        )

    
    son
)
(defun bolucu(str &optional nl)   
    (let 
        ((i 
            (position " " str
		    :from-end t
		    :test #'
            (lambda (a b) (find b a :test #'string=)))
        ))      
        (if i
	        (bolucu (subseq str 0 i) (cons (subseq str (1+ i)) nl))
            (cons str nl)
        )
    )
)

(defun kelime_bak(word list1 list2)
    (let ((len (length word)) (word1) (j 0) (index) (temp) (nm 0))
        (setq exit2 0)
        (setq list_rtn (list))
        (loop for i from 1 to len
            do
            (if (equal exit2 1) (setq exit2 0))
            (setq word1 (string-downcase (subseq word j i)))
            (if (and (equal exit2 0) (>= len 2) (string= (subseq word 0 1) comment)) 
                (if (string= (subseq word 1 2) comment)
                    (progn  
                        (setq list1 (cons '"COMMENT" list1))
                        (setq exit2 2)
                    )
                )
            )
            ; OPERATOR MU NE TURU BELLI OLSUNN DIYE
            (if (not (equal (setq list1(opkontrol word word1 list1 list2)) nil ))
                (progn
                    (setq j i) 
                    (setq exit2 1)
                )         
            )             
            ; ONEMLI SYNTAX ICIN
            (setq valbakla (valbak word word1 i j len list1 list2))
            (if (and (equal exit2 0) (not (equal valbakla nil)) )
                (progn 
                    (setq i valbakla)
                    (setq j i)
                    (setq exit2 1)
                )
            )
            ; KW KONTROLU YAPIYO BOYLECE EXIT DA GOZUKUYOR
            (setq kelimebakla (kwkontrol word word1 i len list1 list2))
            ; exit control
            (if (or (= exit2 -1) (= exit2 2)) (return exit2))
            
        )
    )
)
(defun pulsar (x listkontrol &optional (i 0))
	(if (null listkontrol)
		nil
		(if (string= x (car listkontrol))
			i
			(pulsar x (cdr listkontrol) (+ i 1))
		)
	)
)

;ONEMLI
(defun hizmetci_val (x)
	(let ((lett "") (index t))
		(if (equal (every #'digit-char-p x) nil)
			(setq index nil) 
			(setq index t) 
		)
		index	
	)
)