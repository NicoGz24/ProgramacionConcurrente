Se desea modelar el funcionamiento de un banco en el cual existen 5 cajas para realizar
pagos. Existen P clientes que desean hacer un pago. Para esto, cada una selecciona la caja
donde hay menos personas esperando; una vez seleccionada, espera a ser atendido. En cada
caja, los clientes son atendidos por orden de llegada. Luego del pago, se les entrega un
comprobante. Nota: maximizando la concurrencia.

chan cajas[5](int)   //arreglo de colas para cada una de las cajas
chan comprobantes[P](text)
chan clientes[P](int)  //arreglo de colas privadas para cada cliente donde esta la caja que se le asigno
chan pedidos(int)
chan salida(int)  //cola de cajas liberadas

process Cliente[id:0..P-1]
{
    int caja
    text comp
    send pedidos(id) //aviso que llegue
    receive clientes[id](caja) //espero que me asignen una caja
    send cajas[caja](id)  //me encolo en la caja asiganda
    receive comprobantes[id](comp)    //espero mi comprobante de pago
    send salida(caja)   //aviso que me fui de la caja para liberarla
}

process Cajero[id:0..4]
{
    int idCliente
    text comp
    while (true){
        receive cajas[id](idCliente)  
        Atender(idCliente)
        GenerarComprobante(comp)
        send comprobantes[idCliente](comp)
    }
}

process Coordinador::
{
    int idCliente, caja, min
    int canCli[5] = ([5],0)
    while(true)
    {
        if (not empty(pedidos))
        {
            receive pedidos(idCliente)
            min = canCli[0]
            for i=0 to 4
            {
                if(min > canCli[i])  //calculo la caja con menos cantidad de personas
                {
                    min = canCli[i]
                    caja - i
                }
            }
            canCli[caja]++
            send Clientes[idCliente](caja)
        }
        (not empty (salida))
        {
            receive salida(caja) 
            canCli[caja]--  
        }     
    }
}