CC = g++
CFLAGS = -I ./controller -I ./inputer -I ./reader -I ./writer -I ./session -I ./json_spirit/ciere/json

server_obj = server.o ./controller/server_trans_controller.o \
   ./inputer/data_inputer.o ./inputer/session_data_inputer.o \
   ./reader/data_reader.o ./reader/remote_data_reader.o \
   ./writer/data_writer.o ./writer/file_data_writer.o \
   ./session/io_session.o ./session/server_session.o 

client_obj = client.o ./controller/client_trans_controller.o \
   ./inputer/data_inputer.o ./inputer/cin_data_inputer.o \
   ./reader/data_reader.o ./reader/file_data_reader.o \
   ./writer/data_writer.o ./writer/remote_data_writer.o \
   ./session/client_session.o    

all : server client
.PHONY : all

server : $(server_obj)
	$(CC) -o server $(server_obj) -L ./json_spirit/build -l json -lpthread

$(server_obj) : %.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

client : $(client_obj)
	$(CC) -o client $(client_obj) -L ./json_spirit/build -l json

$(client_obj) : %.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm $(server_obj) $(client_obj)

