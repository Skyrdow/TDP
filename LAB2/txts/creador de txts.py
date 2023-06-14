# Script para generar txts rapido
# Chatgpt lo hizo

def crear_archivos(diccionario):
    for nombre_archivo, contenido in diccionario.items():
        with open("txts/" + nombre_archivo + '.txt', 'w') as archivo:
            archivo.write(contenido)
        
        print(f"Archivo '{nombre_archivo}' creado y contenido escrito.")

# Ejemplo de uso
diccionario_archivos = {
    "sub_1": "- x x",
    "sub_2": "- * 2 x * x 2",
    "sub_3": "- x 0",
    "add_1": "+ 0 x",
    "add_2": "+ - x x y",
    "add_3": "+ x x",
    "add_4": "+ * x y * x y",
    "add_5": "+ x - 0 x",
    "add_6": "+ x * 5 x",
    "add_7": "+ * x y * 5 * x y",
    "add_8": "+ x * y x",
    "add_9": "+ * 4 x * 7 x", 
    "mul_1": "* x 0",
    "mul_2": "* * x 5 1",
    "pow_1": "^ 0 x",
    "pow_2": "^ + x 1 1",
    "pow_3": "^ + x y 0",
    "expr1": "+ + + 1 x + 1 x + + 1 x + + 1 x 1",
    "expr2": "+ 1 + x + 1 + y + 1 + x 1",
    "expr3": "+ 1 x + 1 - 1 x",
    "expr4": "+ + 1 ^ x 2 + 1 ^ x 2",
    "expr5": "+ + 1 * 2 x + 1 * 3 x",
    "expr6": "- ^ - 1 x 8 ^ - 1 x 8",
    "derv1": "^ + x y 2",
    "derv2": "* + x y + 2 ^ x 3",
}

crear_archivos(diccionario_archivos)
