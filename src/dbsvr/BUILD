
cc_library(
	name = 'libdbsvr_client',
	srcs = [
		'dbsvr.pb.cc',
		'dbsvr_client.cpp',
		'phxrpc_dbsvr_stub.cpp',
	],
	deps = [
		'#phxrpc',
	],
    export_incs = ['.',],
	extra_cppflags = [ 
		'-Wall',
		'-Werror',
	]
)

cc_binary(
	name = 'dbsvr_main',
	srcs = [
		'dbsvr.pb.cc',
		'dbsvr_service_impl.cpp',
		'phxrpc_dbsvr_service.cpp',
		'phxrpc_dbsvr_dispatcher.cpp',
		'dbsvr_server_config.cpp',
		'dbsvr_main.cpp',
	],
	deps = [
		'#phxrpc',
		],
	extra_cppflags = [ 
		'-Wall',
		'-Werror',
		'-std=gnu++11',
	]
)

cc_binary(
	name = 'dbsvr_tool_main',
	srcs = [
		'dbsvr.pb.cc',
		'phxrpc_dbsvr_tool.cpp',
		'dbsvr_tool_impl.cpp',
		'dbsvr_tool_main.cpp',
		'dbsvr_server_config.cpp',
		'dbsvr_main.cpp',
	],
	deps = [
		'#phxrpc',
		':libdbsvr_client',
		],
	extra_cppflags = [ 
		'-Wall',
		'-Werror',
		'-std=gnu++11',
	]
)