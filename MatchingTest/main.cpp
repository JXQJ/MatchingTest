#include <opencv2/opencv.hpp>
#include <exception>
#include <Windows.h>
#include "DirectionEstimator.h"

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

int main() {
	//string rootPath = "D:\\Research\\�@����\\�����_����\\20160802\\straight_right_curve\\img\\";
	string rootPath = "D:\\Research\\�@����\\�����_����\\20160802\\straight_look_around\\img\\";

	DirectionEstimator de;

	//de.setIsSaveImg(true);
	//vector<string> imgFiles = getFiles(rootPath, "*.jpg");
	//while (imgFiles.size() > 0) {
	//	cout << "-> " << imgFiles.size() << endl;
	//	Mat cameraImg = imread(rootPath + imgFiles.front());
	//	de.estimate(cameraImg);
	//	imgFiles.erase(imgFiles.begin());
	//	waitKey(50);
	//}
	//de.logVanishPointHistory("vanishPointHistory.txt");

	de.readVanishPointHistory("vanishPointHistory.txt");
	de.drawVanishPointHistory();
	waitKey(0);
	destroyAllWindows();

	return 0;
}