#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}


void Tools::NormAng(double *ang) {
	while (*ang > M_PI) *ang -= 2. * M_PI;
	while (*ang < -M_PI) *ang += 2. * M_PI;
}
VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
	static VectorXd rmseVec = VectorXd(4);
	rmseVec << 0, 0, 0, 0;
	// Check the validity of the following inputs:
	// The estimation vector size should not be zero
	if (estimations.size() == 0) {
		cout << "Input is empty" << endl;
		return rmseVec;
	}
	// The estimation vector size should equal ground truth vector size
	if (estimations.size() != ground_truth.size()) {
		cout << "Invalid estimation or ground_truth. Data should have the same size" << endl;
		return rmseVec;
	}
	// Accumulate squared residuals
	for (unsigned int i = 0; i < estimations.size(); ++i) {
		VectorXd residual = estimations[i] - ground_truth[i];
		// Coefficient-wise multiplication
		residual = residual.array()*residual.array();
		rmseVec += residual;
	}
	// Calculate the mean
	rmseVec = rmseVec / estimations.size();
	rmseVec = rmseVec.array().sqrt();
	return rmseVec;
}
