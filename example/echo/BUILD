cc_binary(
	name = 'EchoServer',
	srcs = [
		'Server.cpp',
	],
	deps = [
		'//src/net:LightServerNet',
	],
	extra_cppflags = [ 
		'-Wall',
		#'-Werror',
		'-std=gnu++11',
	]
)

cc_binary(
	name = 'EchoClient',
	srcs = [
		'Client.cpp',
	],
	deps = [
		'//src/net:LightServerNet',
	],
	extra_cppflags = [ 
		'-Wall',
		#'-Werror',
		'-std=gnu++11',
	]
)