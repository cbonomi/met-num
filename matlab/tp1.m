function tp1(p)
W = importdata("/home/christian/matriz"," ",0); %nos guardamos la matriz del archivo en W
[m,n] = size(W) % n tiene el tamaño de W
c_j = sum(W) % c_j es un vector con la cantidad de links que referencian a  cada pagina
% creamos la matriz diagonal D con 1/c_j en cada posicion si c_j != 0 y 0
% sino
D = diag(arrayfun(@(x) dividir_si_es_posible(x),c_j)) 
I=eye(n) % I = matriz identidad
b = ones(n,1) % b = vector columna de de unos
(I-p.*D*W)\b % resolvemos el sistema 

I-p.*D*W

function y = dividir_si_es_posible(x)
if (x ==0)
    y = 0
else
    y = 1/x
end