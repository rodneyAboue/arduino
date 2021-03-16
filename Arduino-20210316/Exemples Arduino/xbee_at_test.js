var USB = require("./usb.js").USB

var xbee = new USB("/dev/ttyACM0",{callback : 
	function (s) {
		console.log("XBEE : "+s)
	}
})

setTimeout(() => {
	xbee.port.write("essai\n")
}, 1000)


