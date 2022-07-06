server:server.cpp
	g++ -o server server.cpp ../controller/server_trans_controller.cpp \
	../inputer/session_data_inputer.cpp ../inputer/data_inputer.cpp \
	../reader/data_reader.cpp ../reader/remote_data_reader.cpp \
	../writer/data_writer.cpp ../writer/file_data_writer.cpp \
	../session/server_session.cpp ../session/io_session.cpp \
	-I ../controller -I ../inputer -I ../reader -I ../writer -I ../session -lpthread