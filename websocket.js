const http = require('http');
const WebSocket = require('websocket').server;

const server = http.createServer((request, response) => {
  // No es necesario implementar nada para HTTP en este ejemplo
});

const wsServer = new WebSocket({
  httpServer: server,
});

wsServer.on('request', (request) => {
  const connection = request.accept(null, request.origin);
  
  // Manejar mensajes recibidos
  connection.on('message', (message) => {
    if (message.type === 'utf8') {
      console.log('Mensaje recibido:', message.utf8Data);
      // Aquí puedes enviar una respuesta al cliente si es necesario
      // connection.sendUTF('Respuesta: ' + message.utf8Data);
    }
  });

  // Manejar la conexión cerrada
  connection.on('close', (reasonCode, description) => {
    console.log('Conexión cerrada:', reasonCode, description);
  });
});

// Iniciar el servidor
const port = 8080; // Puedes cambiar el puerto si es necesario
server.listen(port, () => {
  console.log('Servidor de WebSockets escuchando en el puerto', port);
})