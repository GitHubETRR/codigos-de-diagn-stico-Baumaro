""" CUANDO SE TIENE UNA FUNCION LAMBDA SE ESCRIBE DE ESTE MODO """  

    lambda variable: / "expresion" / # esto para una lambda normal

"""   CUANDO SE QUIERE APLICAR UNA FUNCION LAMBDA A UN ITERABLE SE ESCRIBE DE ESTE MODO     """

    variable_para_alojar_el_resultado = / "funcion"(/ "iterable" / , key=lambda variable: criterio) /

""" key=lambda lo que hace es establecer que el la funcion va a ser la expresion que evalue el iterable"""

""" variable: criterio /// hace que a cada varible del iterable le asigne un criterio para ser evaluados, por ejemplo len(criterio) """