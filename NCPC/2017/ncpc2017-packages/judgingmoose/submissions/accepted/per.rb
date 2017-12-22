# I have no idea what I'm doing.

nums = STDIN.read.split().map(&:to_i)
l = nums[0]
r = nums[1]
val = 2 * nums.max
if val == 0
  puts "Not a moose"
elsif l == r
  puts "Even " + val.to_s
else
  puts "Odd " + val.to_s
end
