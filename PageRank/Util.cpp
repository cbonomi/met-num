Matriz leerMatriz(string nombreArchivo) {
    std::fstream entrada(nombreArchivo, std::ios_base::in);

    int cantidadTotalDePaginas;
    int cantidadTotalDeLinks;


    entrada >> cantidadTotalDePaginas >> cantidadTotalDeLinks;

    Matriz ret(cantidadTotalDePaginas, cantidadTotalDeLinks);

    int i, j;

    while (entrada >> i >> j)
        ret.set(i, j, 1);

    entrada.close();

    return ret;
}

void escribirRanking(string nombreArchivo, std::vector<float> ranking, float probabilidadDeSaltar) {
    std::ofstream salida(nombreArchivo, std::ios_base::out);

    salida << probabilidadDeSaltar << '\n';

    for (std::vector<float>::iterator it = ranking.begin() ; it != ranking.end(); ++it)
        salida << *it << '\n';

    salida.close();
}
