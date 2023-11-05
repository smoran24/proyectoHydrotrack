const http = require('http');
const WebSocket = require('websocket').server;
const mysql = require('mysql'); // Importa el paquete MySQL

const server = http.createServer((request, response) => {
  // No es necesario implementar nada para HTTP en este ejemplo
});

const wsServer = new WebSocket({
  httpServer: server,
});

// Configura la conexión a tu base de datos MySQL
const dbConnection = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'hydrotrack',
});

wsServer.on('request', (request) => {
  const connection = request.accept(null, request.origin);
  
  // Manejar mensajes recibos
  connection.on('message', (message) => {
    if (message.type === 'utf8') {
      console.log('Mensaje recibido:', message.utf8Data);

      // Descompone el mensaje en sus elementos Flow y Volumen
      const data = message.utf8Data.split(', ');
      console.log("data",data);
      const flow = parseFloat(data[0].split(' ')[1]);
      console.log("flow",flow);      
      const volume = parseFloat(data[1].split(' ')[1]);
      console.log("volume",volume);      

      // Inserta los datos en la tabla "mediciones" de MySQL
      const insertQuery = `INSERT INTO mediciones (flow, volumen) VALUES (${flow}, ${volume})`;

      dbConnection.query(insertQuery, (error, results, fields) => {
        if (error) {
          console.error('Error al insertar datos en MySQL:', error);
        } else {
          console.log('Datos almacenados en MySQL con éxito.');
        }
      });
    }
  });

  // Manejar la conexión cerrada
  connection.on('close', (reasonCode, description) => {
    console.log('Conexión cerrada:', reasonCode, description);
  });
});

// Iniciar el servidor
const port = 3000; // Puedes cambiar el puerto si es necesario
server.listen(port, () => {
  console.log('Servidor de WebSockets escuchando en el puerto', port);
});
