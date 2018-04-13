function tp1()
format short
nombreArchivo = "/home/leandro/CLionProjects/met-num-TP1/tests_tp1/test_15_segundos.txt"
p = 0.85
W = construirMatriz(nombreArchivo)%importdata("/home/christian/matriz"," ",0); %nos guardamos la matriz del archivo en W
[m,n] = size(W) % n tiene el tamaño de W
c_j = sum(W) % c_j es un vector con la cantidad de links que referencian a  cada pagina
% creamos la matriz diagonal D con 1/c_j en cada posicion si c_j != 0 y 0
% sino
D = diag(arrayfun(@(x) dividir_si_es_posible(x),c_j)) 
I=eye(n) % I = matriz identidad
b = ones(n,1) % b = vector columna de de unos
sol = (I-p.*W*D)\b % resolvemos el sistema
b_ordenado = sort(sol)
escala = sum(b_ordenado) 
arrayfun(@(x) x/escala,sol)
%whos D
%sol
%I-p.*W*D


function y = dividir_si_es_posible(x)
if (x ==0)
    y = 0
else
    y = 1/x
end

function num = convertir_a_numerico(str)
   str_tam = cell2mat(str)
   num = str2double(str_tam)

function ret = construirMatriz(nombreArchivo)
    datos = importdata(nombreArchivo," ",2)
    datos(1)
    if class(datos) == "cell"
        n = convertir_a_numerico(datos(1))
        ret = zeros(n,n) %sparse
    else
        n = convertir_a_numerico(datos.textdata(1))
        ret = zeros(n,n) %sparse
        posiciones_donde_hay_1 = datos.data

        for i = 1:size(posiciones_donde_hay_1,1)
            ret(posiciones_donde_hay_1(i,2), posiciones_donde_hay_1(i,1)) = 1
        end

    end
    
            
