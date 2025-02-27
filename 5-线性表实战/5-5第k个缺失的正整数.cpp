class Solution
{
public:
    int findKthPositive(vector<int> &arr, int k)
    {
        int num = 1, pos = 0;
        while (k != 0)
        {
            if (pos >= arr.size() || pos < arr.size() && arr[pos] != num)
                --k;
            else
                ++pos;
            ++num;
        }
        return num - 1;
    }
};

// var findKthPositive = function (arr, k) {
//     for (var i = 0; i < arr.length; i++) {
//         if (arr[i] <= k) {
//             k++
//         }
//     }

//     return k
// };