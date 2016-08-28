var serialport = require('serialport');
var portName = '/dev/ttyACM0';

var express = require ('express'); 
var app = express(); 
app.set('port', process.env.PORT || 3000);

var temp = 0;

var sp = new serialport(portName, {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: serialport.parsers.readline("\r\n")
});

//chamada continua ao stream da porta serial
sp.on('data', function(input) {
	temp = input;
    console.log(input);
});

//configuração do listener na porta
app.listen(app.get('port'), function(){

	console.log('Servidor foi iniciado corretamente, pressione Ctrl+C a qualquer momento para finalizá-lo. ');

});
 
 //servico mensagem, recebe parametro msg como mensagem  e envia para porta serial e mostra no log
app.get('/mensagem', function(req, res){

	console.log('\n\n\n******' + req.query.msg);

	sp.write("#>"+req.query.msg);
	res.send("Mensagem <b>" + req.query.msg + "</b> enviada com sucesso ao sistema.");

});

//metodo para leitura da temperatura
app.get('/temperatura', function(req, res){
	
    res.send(temp);
});

//metodo para acender lampada
app.get('/acendeLampada', function(req, res){

	sp.write("#&t");
	res.send("Lâmpada<b> ACESA </b> com sucesso.");
});

//metodo para apagar lampada
app.get('/apagarLampada', function(req, res){

	sp.write("#&f");
	res.send("Lâmpada<b> APAGADA </b> com sucesso.");
});
