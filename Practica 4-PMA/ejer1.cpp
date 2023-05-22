1. Suponga que N personas llegan a la cola de un banco. Para atender a las personas existen 2
empleados que van atendiendo de a una y por orden de llegada a las personas.

chan clientes(int)

process Cliente[id:0..N-1]
{
    send clientes(id)
}

process Empleado[id:0..1]
{
    int idCliente
    while(true)
    {
        receive clientes(idCliente)
        Atender(idCliente)
    }        
}