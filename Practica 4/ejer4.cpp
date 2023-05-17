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

process Cliente [id:0..N-1]
{
    int cabina
    text ticket
    send pedidos(id)
    receive cabinasClie[id](cabina)
    UsarCabina(cabina)
    send cabinasLibres(cabina)
    send pedidosCobro(id)
    receive tickets[id](ticket)
}

process Empleado::
{
    int idCli
    text ticket
    int cabina
    while(true)
    {
        if(not empty(pedidosCobro))
        {
            receive pedidosCobro(idCli)
            Cobrar(idCli)
            GenerarTicket(ticket)
            send tickets[idCli](ticket)
        }
        else  // este else no podria generar busy waiting ?? si estan todas las cabinas ocupadas y no hay nadie para pagar, se queda loopeando en el while
        {
            if (not empty(cabinasLibres))
            {
                receive cabinasLibres(cabina)
                receive pedidos(idCli)
                send cabinasCli[idCli](cabina)
            }
        }
    }
}