Se quiere modelar la cola de un banco que atiende un solo empleado, los clientes llegan y si
esperan más de 10 minutos se retiran.

procedure Banco is

    Task Empleado is
        Entry atender()
    end Empleado

    Task Type Cliente;
    arrClientes: array(1..N) of Cliente

    Task Body Empleado is
    begin
        loop
            Accept atender()
        end loop
    end Empleado

    Task Body Cliente is
    begin  
        SELECT Empleado.atender()
        OR DELAY 10min
            null;
        end SELECT
    end Cliente
begin

end