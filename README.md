# 🍝 Philosophers - Sincronización de Hilos y Recursos

## 📌 Descripción

**Philosophers** es un proyecto del cursus de 42 que simula el famoso problema de los **Filósofos Comensales**, una metáfora clásica en la programación concurrente. El objetivo es gestionar correctamente el uso de recursos compartidos (tenedores) entre múltiples hilos (filósofos) sin caer en **condiciones de carrera**, **deadlocks** o **starvation**.

Cada filósofo alterna entre pensar, comer y dormir. Para comer, necesita adquirir dos tenedores (mutex). El reto radica en evitar bloqueos mutuos mientras se garantiza que ningún filósofo muera de hambre.


## 🎯 Objetivos y Reglas

- Simular la vida de **n** filósofos sentados alrededor de una mesa.
- Cada filósofo necesita **dos tenedores** (uno a cada lado) para comer.
- Si un filósofo no come dentro del tiempo `time_to_die`, **muere**.
- El programa finaliza cuando **un filósofo muere** o todos han comido `x` veces (si se especifica).
- Usar hilos (`pthread`) y **mutexes** para la sincronización.
- **Prohibido** usar semáforos en esta versión.


## 🧪 Uso

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Argumentos:

- `number_of_philos`  
  Número de filósofos y tenedores.

- `time_to_die`  
  Tiempo máximo sin comer antes de morir (en milisegundos).

- `time_to_eat`  
  Tiempo que tarda un filósofo en comer (en milisegundos).

- `time_to_sleep`  
  Tiempo que tarda un filósofo en dormir (en milisegundos).

- `number_of_times_each_philosopher_must_eat` (opcional)  
  Si todos los filósofos comen esta cantidad de veces, la simulación finaliza con éxito.

### Ejemplo:

```bash
./philo 5 800 200 200
```


## 🖥️ Compilación

```bash
make        # Compila el programa
make clean  # Elimina archivos objeto
make fclean # Elimina archivos objeto y el binario
make re     # Recompila desde cero
```


## 🏗️ Estructura del Proyecto

```
📂 philo/
├── Makefile             # Instrucciones de compilación
├── main.c               # Punto de entrada: validaciones y llamada a entrance()
├── philo.c              # Inicialización de filósofos, forks y monitor
├── config.c             # Parseo y validación de argumentos, init de mutexes
├── philo_routine.c      # Rutina principal de cada filósofo y el monitor de muerte
├── philo_actions.c      # Implementación de take_forks, eat, sleep_and_think
├── utils.c              # ft_get_current_time, ft_print_status
├── philo_utils.c        # check_single_philo, check_philo_death, check_all_full
├── ft_atoi.c            # Implementación de ft_atoi y ft_isdigit/isspace
└── philo.h              # Estructuras y prototipos de funciones
```


## 🧠 Lógica del Programa

1. **Inicialización**  
   - Parseo y validación de argumentos con `ft_atoi()` y `ft_isdigit()`.  
   - Configuración de `t_global_config` (tiempos, número de filósofos, mutexes).  
   - Reserva y creación de forks (mutexes) y array de hilos.

2. **Ejecución de hilos**  
   - Cada filósofo se lanza en un hilo que ejecuta `routine()`:  
     1. Pensar  
     2. Tomar tenedores (mutex)  
     3. Comer  
     4. Soltar tenedores  
     5. Dormir  

3. **Monitor de muerte**  
   - Un hilo independiente recorre la lista de filósofos cada 5 ms.  
   - Si detecta un filósofo sin comer dentro de `time_to_die`, imprime el estado de “died” y marca finalización.

4. **Finalización**  
   - Si un filósofo muere, todos los hilos terminan pronto.  
   - Si se especifica `max_meals` y todos los filósofos alcanzan esa cuenta, el monitor detiene la simulación.


## 🔐 Protección de Concurrencia

- **Forks**: cada tenedor es un `pthread_mutex_t`.  
- **Print**: `mutex_print` evita solapamiento en la salida por consola.  
- **Estado global**: `someone_died` y `all_philos_full` protegidos por `mutex_eat`.


## ⚙️ Funciones Permitidas

- **Hilos y sincronización**:  
  `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`

- **Tiempo y espera**:  
  `gettimeofday`, `usleep`, cálculo de milisegundos personalizado.

- **I/O y memoria**:  
  `printf`, `write`, `malloc`, `free`


## 📋 Validaciones de Entrada

- Todos los argumentos deben ser **enteros positivos**.  
- Se rechazan caracteres no numéricos o signos incorrectos.  
- Si falla la validación, muestra:

  ```
  Invalid args. Variables needed (all positive):
  philosophers_num (>= 1)
  time_to_die (milliseconds)
  time_to_eat (milliseconds)
  time_to_sleep (milliseconds)
  number_of_times_each_philosopher_must_eat (optional)
  e.g. ./philo 5 200 200 200 3
  ```


## 👀 Comportamiento Esperado

✅ **Entrada válida**  
```bash
./philo 5 800 200 200
```
Salida tipo:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
...
```

❌ **Entrada inválida**  
```bash
./philo 5 -800 200 a
```
Salida:
```
Invalid args. Variables needed (all positive):
...
```


## 📚 Referencias Técnicas

- **Problema original**: Dijkstra, 1965.  
- Temas clave:  
  - Programación concurrente con hilos  
  - Mutexes y sincronización  
  - Evitar deadlocks y starvation  
  - Gestión de tiempo en milisegundos en C

---

## 🤝 Créditos

Proyecto desarrollado por `jcurtidodev` como parte del cursus de **42 School**.
