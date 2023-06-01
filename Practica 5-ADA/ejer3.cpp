Se dispone de un sistema compuesto por 1 central y 2 procesos. Los procesos envían
señales a la central. La central comienza su ejecución tomando una señal del proceso 1,
luego toma aleatoriamente señales de cualquiera de los dos indefinidamente. Al recibir una
señal de proceso 2, recibe señales del mismo proceso durante 3 minutos.
El proceso 1 envía una señal que es considerada vieja (se deshecha) si en 2 minutos no fue
recibida.
El proceso 2 envía una señal, si no es recibida en ese instante espera 1 minuto y vuelve a
mandarla (no se deshecha).

Procedure Sistema instante

    Task Central is
        Entry tomarSeñal1()
        Entry tomarSeñal2() 
    end Central

    Task Type Proceso1;

    Task Type Proceso2;

    Task Timer is
        Entry get_time(tiempo: OUT float) 
        Entry time_out()

    Task Body Proceso1 is
    begin
        SELECT Cetral.tomarSeñal1()
        OR DELAY 2min => null
        end SELECT
    end Proceso1

    Task Body Proceso2 is
    begin
        SELECT Cetral.tomarSeñal2()
        OR DELAY 1 min => Central.tomarSeñal2()
        end SELECT
    end Proceso2

    Task Body Timer is

    end Timer

    Task Body Central is
    begin
        Accept tomarSeñal1()
        loop
            SELECT accept tomarSenal1()
            OR  accept tomarSeñal2()
                loop (timer.get_time() < 3 min)
                    SELECT accept tomarSeñal2()
                    OR timer.timeOut()
                    end SELECT
                end loop
            end SELECT
        end loop
    end Cental

begin
    null
end Sistema