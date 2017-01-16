#include <opencv2/opencv.hpp>
#include <exception>
#include <Windows.h>
#include "DirectionEstimator.h"
#include <fstream>

using namespace cv;
using namespace std;

// �w��t�H���_�̃t�@�C�����擾����
vector<string> getFiles(const string& dir_path, const string& filter) {
	WIN32_FIND_DATAA fd;
	string ss = dir_path + filter;
	HANDLE hFind = FindFirstFileA(ss.c_str(), &fd);

	// �������s
	if (hFind == INVALID_HANDLE_VALUE) throw exception("getFiles failed");

	vector<string> fileList;
	do {
		// �t�H���_�͏���
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
		// �B���t�@�C���͏���
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) continue;
		fileList.push_back(fd.cFileName);
	} while (FindNextFileA(hFind, &fd));
	FindClose(hFind);
	return fileList;
}

bool readMatBinary(std::ifstream& ifs, cv::Mat& in_mat, vector<Point2f>& currentKpts, vector<Point2f>& prevKpts, Point2f& vpMA)
{
	if (!ifs.is_open()){
		return false;
	}

	int rows, cols, type;
	ifs.read((char*)(&rows), sizeof(int));
	if (rows == 0){
		return true;
	}
	ifs.read((char*)(&cols), sizeof(int));
	ifs.read((char*)(&type), sizeof(int));

	in_mat.release();
	in_mat.create(rows, cols, type);
	ifs.read((char*)(in_mat.data), in_mat.elemSize() * in_mat.total());
	cout << "row: " << rows << ", col: " << cols << ", type: " << type << endl;

	currentKpts.clear();
	prevKpts.clear();
	int flowNum;
	ifs.read((char*)(&flowNum), sizeof(int));
	cout << "flowNum: " << flowNum << endl;
	for (int i = 0; i < flowNum; ++i)
	{
		Point2f prevP, currentP;
		ifs.read((char*)(&prevP), sizeof(Point2f));
		ifs.read((char*)(&currentP), sizeof(Point2f));
		prevKpts.push_back(prevP);
		currentKpts.push_back(currentP);
	}
	ifs.read((char*)(&vpMA), sizeof(Point2f));
	cout << "vpMA:(" << vpMA.x << ", " << vpMA.y << ")" << endl;

	return true;
}

bool LoadMatBinary(const std::string& filename, cv::Mat& output, vector<Point2f>& currentKpts, vector<Point2f>& prevKpts, Point2f& vpMA){
	std::ifstream ifs(filename, std::ios::binary);
	return readMatBinary(ifs, output, currentKpts, prevKpts, vpMA);
}

void saveJpgFromDat(const string& rootPath)
{
	DirectionEstimator* de = new DirectionEstimator();
	de->setIsSaveImg(true);
	vector<string> datFiles = getFiles(rootPath, "*.dat");
	while (datFiles.size() > 0) {
		cout << "-> " << datFiles.size() << endl;
		Mat out;
		vector<Point2f> currentKpts;
		vector<Point2f> prevKpts;
		Point2f vpMA;

		LoadMatBinary(rootPath + datFiles.front(), out, currentKpts, prevKpts, vpMA);
		de->drawFromDat(out, currentKpts, prevKpts, vpMA);
		//imwrite(rootPath + datFiles.front() + ".jpg", out);
		datFiles.erase(datFiles.begin());
		waitKey(50);
	}
	delete de;
}

int main() {
	//string rootPath = "D:\\Research\\�@����\\�����_����\\20160906\\around_and_left_curve_light\\img\\";
	//string rootPath = "D:\\Research\\�@����\\�����_����\\20161018\\moverio_2\\img\\";
	//string rootPath = "D:\\Research\\�@����\\�����_����\\20161018\\���O_1\\img\\";
	//string rootPath = "D:\\Research\\�@����\\�����_����\\20170112\\����������\\3F�O\\";

	string rootPath = "D:\\Research\\�@����\\�����_����\\20170112\\log_test\\";
	saveJpgFromDat(rootPath);

/*	DirectionEstimator* de = new DirectionEstimator();
	de->setIsSaveImg(true);
	vector<string> imgFiles = getFiles(rootPath, "*.jpg");
	while (imgFiles.size() > 0) {
		cout << "-> " << imgFiles.size() << endl;
		Mat cameraImg = imread(rootPath + imgFiles.front());

		// �摜����]
		//Mat rotImg(cv::Size(480, 640), cameraImg.type(), cv::Scalar(0, 0, 0));
		//cv::transpose(cameraImg, rotImg);  // �]�u ����� �����v����90�x��] 
		//cv::flip(rotImg, rotImg, 1);    // ���E���] ���v����90�x��]

		de->estimate(cameraImg);
		imgFiles.erase(imgFiles.begin());
		waitKey(50);
	}
	de->logVPHistory("vanishPointHistory.txt");

	waitKey(0);
	destroyAllWindows();
	delete de;
*/	return 0;
}