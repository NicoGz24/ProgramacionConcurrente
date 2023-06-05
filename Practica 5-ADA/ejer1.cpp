/* 
Se requiere modelar un puente de un solo sentido, el puente solo soporta el peso de 5
unidades de peso. Cada auto pesa 1 unidad, cada camioneta pesa 2 unidades y cada camión
3 unidades. Suponga que hay una cantidad innumerable de vehículos (A autos, B
camionetas y C camiones).
a. Realice la solución suponiendo que todos los vehículos tienen la misma prioridad.
b. Modifique la solución para que tengan mayor prioridad los camiones que el resto de los
vehículos.
*/

procedure Puente is
    Task Paso
        Entry pasoAuto()
        Entry pasoCamioneta()
        Entry pasoCamion()
        Entry salir()
    end Paso

    Task Type Vehiculos;
    arrVehiculos: array(1..N) of Vehiculos

    Task Body Vehiculos is
        peso: int
    begin
        if(peso = 1)
            Paso.pasoAuto()
        else if (peso = 2)
            Paso.pasoCamioneta()
        else
            Paso.pasoCamion()
        end if
        Paso.salir()
    end Vehiculos

    Task Body Paso is
        cant: int = 0
    begin
        loop
            SELECT when (cant < 5) => accept pasoAuto() do cant = cant + 1 end pasoAuto
            OR  when (cant < 4) => accept pasoCamioneta() do cant = cant + 2 end pasoCamioneta
            OR  when (cant < 3) => accept pasoCamion() do cant = cant + 3 end pasoCamion
            OR accept salir(peso: IN int) do cant = cant-peso end salir
            end SELECT
        end loop
    end Paso
begin 
    null;
end puente


b) Modifique la solución para que tengan mayor prioridad los camiones que el resto de los
vehículos.

procedure Puente is
    Task Paso
        Entry pasoAuto()
        Entry pasoCamioneta()
        Entry pasoCamion()
        Entry salir(peso: IN int)
    end Paso

    Task Type Vehiculos;
    arrVehiculos: array(1..N) of Vehiculos

    Task Body Vehiculos is
        peso: int
    begin
        if(peso = 1)
            Paso.pasoAuto()
        else if (peso = 2)
            Paso.pasoCamioneta()
        else
            Paso.pasoCamion()
        end if
        Paso.salir(peso)
    end Vehiculos

    Task Body Paso is
        cant: int = 0
    begin
        loop
            SELECT when (pasoCamion'count = 0) and (cant < 5) => accept pasoAuto() do cant = cant + 1 end pasoAuto
            OR  when (pasoCamion'count = 0) and (cant < 4) => accept pasoCamioneta() do cant = cant + 2 end pasoCamioneta
            OR  when (cant < 3) => accept pasoCamion() do cant = cant + 1 end pasoCamion
            OR accept salir(peso: IN int) do cant = cant-peso end salir
            end SELECT
        end loop
    end Paso
begin 
    null;
end puente