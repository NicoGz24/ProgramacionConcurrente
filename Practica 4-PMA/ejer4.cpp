Simular la atención en un locutorio con 10 cabinas telefónicas, el cual tiene un empleado
que se encarga de atender a N clientes. Al llegar, cada cliente espera hasta que el empleado
le indique a qué cabina ir, la usa y luego se dirige al empleado para pagarle. El empleado
atiende a los clientes en el orden en que hacen los pedidos, pero siempre dando prioridad a
los que terminaron de usar la cabina. A cada cliente se le entrega un ticket factura. 
Nota: maximizar la concurrencia; suponga que hay una función Cobrar() llamada por el empleado
que simula que el empleado le cobra al cliente.

chan pedidos(int)
chan pedidosCobro(int)
chan cabinasCli[N](int)
chan cabinasLibres(int)
chan tickets[N](text)
chan sync() //canal vacio exclusivo para sincronizacion

process Cliente [id:0..N-1]
{
    int cabina
    text ticket
    send pedidos(id)
    send sync() 
    receive cabinasClie[id](cabina)
    UsarCabina(cabina)
    send cabinasLibres(cabina)
    send pedidosCobro(id)
    send sync()
    receive tickets[id](ticket)
}

process Empleado::
{
    int idCli
    text ticket
    int cabina
    for i= 0 to 10
    {
        send cabinasLibres[i]() //inicializacion del canal de cabinas libres
    }
    while(true)
    {
        receive sync()
        if(not empty(pedidosCobro))
        {
            receive pedidosCobro(idCli)
            Cobrar(idCli)
            GenerarTicket(ticket)
            send tickets[idCli](ticket)
        }
        else 
        {
            if (not empty(cabinasLibres))
            {
                receive cabinasLibres(cabina)
                receive pedidos(idCli)
                send cabinasCli[idCli](cabina)
            }
            else
            {
                receive pedidosCobro(idCli)
                Cobrar(idCli)
                GenerarTicket(ticket)
                send tickets[idCli](ticket)
            }
        }
    }
}