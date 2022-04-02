// 一维
for (int i = 0; i < n; ++i) {
  if (i == 0) preSum[i] = nums[i];
  else preSum[i] = preSum[i - 1] + nums[i];
}

// 二维
for (int i = 0; i < rows; ++i) {
  for (int j = 0; j < cols; ++j) {
    if (i == 0 && j == 0) preSum[i][j] = nums[i][j];
    else if (i == 0) preSum[i][j] = preSum[i][j - 1] + nums[i][j];
    else if (j == 0) preSum[i][j] = preSum[i - 1][j] + nums[i][j];
    else preSum[i][j] = preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1] + nums[i][j];
  }
}
