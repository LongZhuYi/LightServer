cc_library(
    name =  'LightServerNet',
    srcs = [
    			'Channel.cpp',
    			'EventLoop.cpp',
    			'Socket.cpp',
    			'TcpServer.cpp',
    			'Buffer.cpp',
    			'poll/Epoll.cpp',
    		],
    export_incs = ['.',],
    incs = [ '.',],
    extra_cppflags = [ 
						'-Wall',
						#'-Werror',
						'-std=gnu++11',
					],
    #deps = [ '//thirdparty/hredis:hiredis' ],
)