Suponga que existe un antivirus distribuido en él hay R procesos robots que continuamente
están buscando posibles sitios web infectados; cada vez que encuentran uno avisan la
dirección y continúan buscando. Hay un proceso analizador que se encargue de hacer todas
las pruebas necesarias con cada uno de los sitios encontrados por los robots para
determinar si están o no infectados.

Process Robot [id:0..R-1]{
    text direccion 
    while (true)
    {
        direccion = buscarSitio()
        Coordinador!encontrado(direccion)
    }
    
}

Process Coordinador::
{
    text direccion
    cola buffer
    do Robot[*]?encontrado(direccion) -> push(buffer,direccion)
    □ (not empty(buffer)), Analizador?pedido() -> pop(buffer,direccion), Analizador!analizar(direccion)
    od
}

Process Analizador ::
{
    text direccion
    while (true)
    {
        Coordinador!pedido()
        Coordinador?.analizar(direccion)
        AnalizarSitio(direccion)
    }

}