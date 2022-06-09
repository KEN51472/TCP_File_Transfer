start: client_trans_controller
cin_data_inputer.o:cin_data_inputer.cpp cin_data_inputer.h
	g++ -c cin_data_inputer.cpp -o cin_data_inputer.o
data_inputer.o:data_inputer.cpp data_inputer.h
	g++ -c data_inputer.cpp -o data_inputer.o
client_trans_controller.o:client_trans_controller.cpp cin_data_inputer.h data_inputer.h data_inputer
	g++ -c client_trans_controller.cpp -o client_trans_controller.o
client_trans_controller:cin_data_inputer.o data_inputer.o client_trans_controller.o
	g++ -o client_trans_controller cin_data_inputer.o data_inputer.o client_trans_controller.o
	