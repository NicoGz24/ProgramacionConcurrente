En un laboratorio de genética veterinaria hay 3 empleados. El primero de ellos
continuamente prepara las muestras de ADN; cada vez que termina, se la envía al segundo
empleado y vuelve a su trabajo. El segundo empleado toma cada muestra de ADN
preparada, arma el set de análisis que se deben realizar con ella y espera el resultado para
archivarlo. Por último, el tercer empleado se encarga de realizar el análisis y devolverle el
resultado al segundo empleado.

Process Empleado[id=0]
{
    Muesta m
    while(true){
        m = PrepararMuestra()
        Coordinador!muestra(m)
    }

}

Process Coordinador::
{
    cola buffer
    Muesta m
    do Empleado[0]?muestra(m) -> push(buffer,m)
    □ (not empty(buffer)), Empleado[1]?pedido() -> Empleado[1]!armarSet(pop(buffer))
}

Process Empleado[id=1]
{
    Muestra m
    Set set
    text resul
    while(true){
        Coordinador!pedido()
        Coordinador?armarSet(m)
        set = ArmarSet(m)
        Empleado[2]!analizar(set)
        Empleado[2]?resultado(resul)
        Archivar(resul)
    }
}

Process Empleado[id=2]
{
    Set set
    text resul
    while (true){
        Empleado[1]?analizar(set)
        resul = Analizar(set)
        Empleado[1]!resultado(resul)
    }
}