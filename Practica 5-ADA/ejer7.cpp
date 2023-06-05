/*
Hay un sistema de reconocimiento de huellas dactilares de la policía que tiene 8 Servidores
para realizar el reconocimiento, cada uno de ellos trabajando con una Base de Datos propia;
a su vez hay un Especialista que utiliza indefinidamente. 

El sistema funciona de la siguiente manera: el Especialista toma una imagen de una huella (TEST) 
y se la envía a los servidores para que cada uno de ellos le devuelva el código y el valor de similitud de la huella que más
se asemeja a TEST en su BD; al final del procesamiento, el especialista debe conocer el
código de la huella con mayor valor de similitud entre las devueltas por los 8 servidores.

Cuando ha terminado de procesar una huella comienza nuevamente todo el ciclo. Nota:
suponga que existe una función Buscar(test, código, valor) que utiliza cada Servidor donde
recibe como parámetro de entrada la huella test, y devuelve como parámetros de salida el
código y el valor de similitud de la huella más parecida a test en la BD correspondiente.
Maximizar la concurrencia y no generar demora innecesaria
*/

procedure Sistema_Huellas is 

    Task Type Servidor is
        Entry identificar(pos: IN integer);
        Entry analizar(test: IN Huella, codigo: OUT text, valor: OUT integer);
    end Servidor;

    Task Especialista;

    arrServidores: array(1..8) of Servidor;

    Task Body Servidor is 
        id:integer;
    begin
        accept identificar(pos: IN integer)do id := pos end identificar;
        loop
            accept analizar(test: IN Huella, codigo: OUT text, valor: OUT integer) do 
                Buscar(test, código, valor);
        end loop
    end Servidor;

    Task Body Especialista is 
        test: Huella;
        codigo,actual: text :='default';
        valor,aux: integer :=0;
    begin
        loop
            test:= TomarHuella();
            for i:=1 to 8 do
                Servidores[i].analizar(test,codigo,valor); // OJO CON ESTO, QUEDA EL PROCESO TRABADO HASTA QUE TERMINE EL SERV
                if(valor > aux)then
                    aux:=valor;
                    actual:=codigo;
                end if
            end for
            GuardarResul(test,codigo,valor); //Se guarda el resultado del analisis
        end loop
    end Especialista;

begin
    for i:= 1 to 8 do
        Servidor[i].identificar(i);
end;