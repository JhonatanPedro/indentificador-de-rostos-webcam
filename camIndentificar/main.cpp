#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

	// setando a camera
	VideoCapture cap(0);

	// checando se a camera foi caregada
	if (!cap.isOpened()) {
		cerr << "Erro ao carregar a camera." << endl;
		return -1;
	}

	// carregando e checando se o clasificador foi carregado foi caregada
	CascadeClassifier faceCascade;
	if (!faceCascade.load("haarcascade-frontalface-default.xml")) {
		cerr << "Erro ao carregar o classificador de rosto." << endl;
		return -1;
	}

	int num_faces = 0;
	Mat frame;

	// Laço principal
	while (true) {
		cap >> frame;

		// criando a cor
		Mat gray;
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		// setando a cor
		vector<Rect> faces;
		faceCascade.detectMultiScale(gray, faces, 1.3, 5);

		// criando os retangulos nos rostos
		for (const auto& face : faces) {
			rectangle(frame, face, Scalar(0, 255, 0), 2);
		}

		// criando e amostrando o texto de quantidade de rostos na tela
		num_faces = faces.size();
		ostringstream text;
		text << "Numero de Rostos: " << num_faces;
		putText(frame, text.str(), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

		// iniciando a aplicação e setando a tecla 'q' para sair do progama
		imshow("indentificador de rosto.", frame);

		if (waitKey(1) == 'q') {
			break;
		}
	}

	// finalizando a aplicação
	cap.release();
	destroyWindow;

	return 0;
}