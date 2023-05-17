
5. En un entrenamiento de futbol hay 20 jugadores que forman 4 equipos (cada jugador
conoce el equipo al cual pertenece llamando a la función DarEquipo()). Cuando un equipo
está listo (han llegado los 5 jugadores que lo componen), debe enfrentarse a otro equipo que
también esté listo (los dos primeros equipos en juntarse juegan en la cancha 1, y los otros
dos equipos juegan en la cancha 2). Una vez que el equipo conoce la cancha en la que juega,
sus jugadores se dirigen a ella. Cuando los 10 jugadores del partido llegaron a la cancha
comienza el partido, juegan durante 50 minutos, y al terminar todos los jugadores del
partido se retiran (no es necesario que se esperen para salir).



process jugador (id:0..19){
	int e, c
	e = DarEquipo()
	cancha.esperarEquipo(e,c)
	cancha.partido(c)
	//jugar partido en cancha c
	delay(50minutos)
	cancha.irse(e)
}

Monitor cancha(){
	int equipos[4]  //cantidad de jugadores que van llegando de cada equipo
	bool equiposListos[4] = ([4],false)
	int cancha = 1
	int cantJC[2]=([2],0)  //arreglo para ir sumando los jugadores de cada cancha
	int jugadoresJugando = 0
	cond esperarJ[4]  //donde esperan los que ya llegaron pero faltan compañeros
	cond equipoFormado   //doy aviso de que hay un nuevo equipo formado
	cond barrerasC[2]	//donde se van a dormir los jugadores hasta que lleguen todos los del partido de esa cancha
	

	procedure esperarEquipo(e: in int, c: out int){
		int i = 0
		equipos[e]++
		if (equipos[e] == 5){
			equiposListos[e] = true
			signalall(esperarJ[e])
			signal(equipoFormado)
		}
		else{
			wait(esperarJ[e])
		}
		while (i > 4){
			if ( i != e) and (equiposListos[i] = true){
				c = cancha
				cancha++
				equiposListos[i] = false
				equiposListos[e] = false
			}
			else{
				if(i == 4){
					i = 0
					wait(equipoFormado)
				}
				else{
					i++
				}
			}

		}

	}
	procedure partido(c:in int){
		cantJC[c]++
		if(cantJC[c] == 10)
			signalall(barreraC[c])
		else
			wait(barreraC[c])
		jugadoresJugando++
	}
	procedure irse(){
		cantidadJugadores--
	}
}


Opcion 2

Process jugador[id:0..19]{
	int cancha
	int equipo = DarEquipo()
	Equipos[equipo].formarEquipo(cancha)
	Canchas[cancha].jugar()
	Canchas[cancha].irse()
}


Monitor OrganizarCancha{
	int orden = 0

	procedure OrganizarCancha(c: out int){
		if (orden > 1)
			c = 1
		else
			c = 2
		orden ++
	}
}

Monitor Equipo[1..4]{
	cond esperarJ
	int cantJ = 0
	int idcancha

	procedure formarEquipo(cancha: out int){
		cantJ++
		if(cantJ < 5){
			wait(esperarJ)
		}
		else 
			OrganizarCancha.darCancha(idcancha)
			signalAll(esperarJ)
		cancha = idCancha
	}
}

Monitor Canchas[1..2]{
	int cantJ = 0
	cond esperarJ, finPartido

	procedure jugar(){
		cantJ++
		if(canJ < 10){
			wait(esperarJ)
		}
		else{
			signalAll(esperarJ)
		}
		wait(finPartido)
		//jugar partido
		delay(50 minutos)
	}
	procedure irse(){
		signal(finPartido)
	}
}