function tp1(nombreArchivo, p)
W = construirMatriz(nombreArchivo)%importdata("/home/christian/matriz"," ",0); %nos guardamos la matriz del archivo en W
[m,n] = size(W) % n tiene el tamaño de W
c_j = sum(W) % c_j es un vector con la cantidad de links que referencian a  cada pagina
% creamos la matriz diagonal D con 1/c_j en cada posicion si c_j != 0 y 0
% sino
D = diag(arrayfun(@(x) dividir_si_es_posible(x),c_j)) 
I=eye(n) % I = matriz identidad
b = ones(n,1) % b = vector columna de de unos
sol = (I-p.*D*W)\b % resolvemos el sistema
b_ordenado = sort(sol)
escala = sum(b_ordenado) 
arrayfun(@(x) x/escala,sol)

%I-p.*D*W


function y = dividir_si_es_posible(x)
if (x ==0)
    y = 0
else
    y = 1/x
end

function ret = construirMatriz(nombreArchivo)
    datos = importdata(nombreArchivo," ",2)
    posiciones_donde_hay_1 = datos.data
    str_tam = cell2mat(datos.textdata(1))
    n = str2double(str_tam)
    ret = zeros(n,n) %sparse

    for i = 1:size(posiciones_donde_hay_1,1)
<<<<<<< HEAD
      ret(posiciones_donde_hay_1(i,:)) = 1
=======
        ret(posiciones_donde_hay_1(i,1),posiciones_donde_hay_1(i,2)) = 1
>>>>>>> af733c9fd1b3abd237303401d59e733f8aa64c7c
    end
    ret;
    
    



            
