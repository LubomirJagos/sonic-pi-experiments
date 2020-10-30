=begin
live_loop :foo do
  use_real_time
  data = sync "/osc:192.168.0.122:8888/trigger/prophet"
  data2 = data.map(&:to_i)
  synth :prophet, note: :e1, cutoff: data2[0], release: 8
  sleep 1
end
=end

live_loop :fooAnother do
  use_real_time
  data = sync "/osc:192.168.0.122:8888/trigger/prophet"
  data2 = data.map(&:to_i)
  synth :prophet, note: :e1, cutoff: data2[1], release: data2[0]
  sleep 1
end