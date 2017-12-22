// I have no idea what I'm doing.

var nums = readline().split(' ');
var l = parseInt(nums[0]);
var r = parseInt(nums[1]);
var val = 2 * Math.max(l, r);
if (val == 0) {
    print("Not a moose");
} else if (l == r) {
    print("Even " + val);
} else {
    print("Odd " + val);
}
