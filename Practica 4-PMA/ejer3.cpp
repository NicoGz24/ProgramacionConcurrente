Se debe modelar el funcionamiento de una casa de comida rápida, en la cual trabajan 2
cocineros y 3 vendedores, y que debe atender a C clientes. El modelado debe considerar
que:
- Cada cliente realiza un pedido y luego espera a que se lo entreguen.
- Los pedidos que hacen los clientes son tomados por cualquiera de los vendedores y se
lo pasan a los cocineros para que realicen el plato. Cuando no hay pedidos para atender,
los vendedores aprovechan para reponer un pack de bebidas de la heladera (tardan entre
1 y 3 minutos para hacer esto).
- Repetidamente cada cocinero toma un pedido pendiente dejado por los vendedores, lo
cocina y se lo entrega directamente al cliente correspondiente.
Nota: maximizar la concurrencia

chan pedidos (int, text)
chan pedidosListos[C](Pedido)
chan cocineros(int, text)
chan vendedor[3](int,text)
chan pedidoVendedor(int)

process Cliente[id:0..C-1]
{
    text pedido
    Pedido pListo
    ArmarPedido(pedido)
    send pedidos(id, pedido)  //hago mi pedido
    receive pedidosListos[id](pListo)  //me quedo esperando a que me entreguen el pedido
}

process Coordinador::
{
    int idCli, idVend
    text pedido
    while (true)
    {
        receive pedidoVendedor(idVend) //espero a que un vendedor se libere y pida un pedido
        if(empty (pedidos))
        {
            send vendedor[idVend](0,'VACIO') //le aviso al vendedor que no hay pedidos
        }
        else
        {
            receive pedidos(idCli,pedido)
            send vendedor[idVend](idCli,pedido)
        }
    }
}

process Vendedor[id:0..2]
{
    int idCli
    text pedido
    while (true)
    {
        send pedidoVendedor(id)
        receive vendedor[id](idCli, pedido)
        if( pedido = 'VACIO')
        {
            delay(3min)
            ReponerBebidas()
        }
        else{
            send cocineros(idCli,pedido)
        }
    }
}

process Cocinero[id:0..1]
{
    int idCli
    text pedido
    Pedido pListo
    while(true)
    {
        receive cocineros(idCli,pedido)
        Cocinar(pedido,pListo)
        send pedidosListos[idCli](pListo)
    }
}