# proyectoHydrotrack

Diseño de prototipo de sistema de medición de consumo de agua en hogares particulares

En este proyecto se plantea diseñar un prototipo de sistema de medición del caudal de agua domiciliario con los objetivos de concientizar sobre el consumo de este recurso, y permitirle a los usuarios acceder a información pertinente en tiempo real. Con este sistema se espera reducir el consumo del agua. Para lograrlo se busca emplear tecnologías IoT basadas en hardware abierto como un módulo ESP8266, un caudalímetro y plataformas para aplicaciones basadas en la nube. El caudalímetro mide tanto volumen como flujo de agua en la tubería donde está instalado. Entonces, el dispositivo puede instalarse en la línea de entrada principal de agua o en la línea de entrada a un área específica (baño o cocina). También se puede instalar en la línea de salida del calefón para medir el consumo de agua caliente. Se apunta a usar un servicio web para complementar este sistema, a través de la cual obtener los datos sobre consumo y mostrar diagramas a los usuarios.

En este repositorio se incluyen los archivos del servidor node.js (sin incluir la carpeta node_modules), y el archivo .ino del codigo arduino para el ESP8266
