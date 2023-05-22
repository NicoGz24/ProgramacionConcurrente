Resolver la administración de las impresoras de una oficina. Hay 3 impresoras, N usuarios y
1 director. Los usuarios y el director están continuamente trabajando y cada tanto envían
documentos a imprimir. Cada impresora, cuando está libre, toma un documento y lo
imprime, de acuerdo con el orden de llegada, pero siempre dando prioridad a los pedidos
del director. 
Nota: los usuarios y el director no deben esperar a que se imprima el documento.

chan pedidosUsu(int)
chan impresorasUsu[N](int)
chan pedidosDire(int)
chan impresoraDire(int)
chan impresorasLibres(int)
chan sync()

process Usuario[id:0..N-1]
{
    text documento
    int impresora
    GenerarDocumento(documento)
    send pedidosUsu(id)
    send sync()
    receive impresorasUsu[id](impresora)
    Imprimir[impresora](documento)
    send impresorasLibres(impresora)
}

process Director::
{
    text documento
    int impresora
    GenerarDocumento(documento)
    send pedidosDire(1)
    receive impresorasDire(impresora)
    Imprimir[impresora](documento)
    send impresorasLibres(impresora)
}

process Coordinador::
{
    int id
    int impresora
    for i = 0 to 3
    {
        send impresorasLibres() //inicializacion del canal de impresoras libres
    }
    while (true)
    {
        receive impresorasLibres(impresora)
        recive sync()
        if(not empty(pedidosDire))
        {
            receive pedidosDire(id)
            send impresoraDire(impresora)
        }
        else
        {
            receive pedidosUsu(id)  
            send impresorasUsu[id](impresora)
        }
    }
}