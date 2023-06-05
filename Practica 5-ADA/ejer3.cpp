/*Se dispone de un sistema compuesto por 1 central y 2 procesos. Los procesos envían
señales a la central. La central comienza su ejecución tomando una señal del proceso 1,
luego toma aleatoriamente señales de cualquiera de los dos indefinidamente. Al recibir una
señal de proceso 2, recibe señales del mismo proceso durante 3 minutos.
El proceso 1 envía una señal que es considerada vieja (se deshecha) si en 2 minutos no fue
recibida.
El proceso 2 envía una señal, si no es recibida en ese instante espera 1 minuto y vuelve a
mandarla (no se deshecha). 
*/

Procedure Sistema is

    Task Central is
        Entry tomarSeñal1()
        Entry tomarSeñal2() 
    end Central

    Task Type Proceso1;

    Task Type Proceso2;

    Task Reloj;

    Task Timer is
        Entry get_time(hora: OUT integer) 
        Entry tick()
    end Timer

    Task Body Reloj is
    begin
        loop
            delay (1) 
            Timer.tick() 
        end loop
    end Reloj

    Task Body Proceso1 is
    begin
        loop
            SELECT Cetral.tomarSeñal1()
            OR DELAY 120 => null
            end SELECT
        end loop
    end Proceso1

    Task Body Proceso2 is
    begin
        loop
            SELECT Cetral.tomarSeñal2()
            OR DELAY 60 => Central.tomarSeñal2()
            end SELECT
        end loop
    end Proceso2

    Task Body Timer is
        actual: integer := 0
        auxId ,auxHora: integer
    begin
        loop
            SELECT when (tick`count = 0) => accept get_time(hora: OUT integer) do hora := actual end get_time
            OR accept tick();
                actual := actual+1;
            end SELECT
        end loop
    end Timer
    
    Task Body Central is
        tiempoFin,actual: integer = 0
    begin
        Accept tomarSeñal1()
        loop
            SELECT accept tomarSenal1()
            OR  accept tomarSeñal2();
                Timer.get_time(tiempoFin)
                tiempoFin := tiempoFin + 180 --le sumo 180 segundos = 3 minutos 
                loop (timer.get_time(actual) < tiempoFin)
                    accept tomarSeñal2()
                end loop
            end SELECT
        end loop
    end Cental

begin
    null
end Sistema