#abstract parent class definition
class InstructionAbstract

  def expand(command_array,cmd) ##abstract method to be overridden###
  end

  def InsType(x) #common method for all subclasses
    n=x.length
    if (x[1]==="?")
      return(4)
    elsif((x[2]==='x' || x[2]==='y' || x[2]==='w' || x[2]==='z')&(x[n-1]==='x' || x[n-1]==='y' || x[n-1]==='w' || x[n-1]==='z'))
      return(1)
    elsif((x[2]==='x' || x[2]==='y' || x[2]==='w' || x[2]==='z')&(x[n-1]!='x' || x[n-1]!='y' || x[n-1]!='w' || x[n-1]!='z'))
      return(2)
    else
      return(3)
    end
  end
end

#class for expression types 1(id = id op id) and 2(id = id op constant)
class ExpressionType12 < InstructionAbstract

  def expand(command_array,cmd)

    expression = ''
    op1 = ''
    op2 = ''
    n = command_array[cmd].length

    if command_array[cmd][3] == '*' && command_array[cmd][4] == "*"
      operator = '**'
    else
      operator = command_array[cmd][3].to_s
    end

    if command_array[cmd][2] == 'x'
      op1 = $x.to_s
    elsif command_array[cmd][2] == 'y'
      op1 = $y.to_s
    elsif command_array[cmd][2] == 'z'
      op1 = $z.to_s
    elsif command_array[cmd][2] == 'w'
      op1 = $w.to_s
    end

    if command_array[cmd][n-1] == 'x'
      op2 = $x.to_s
    elsif command_array[cmd][n-1] == 'y'
      op2 = $y.to_s
    elsif command_array[cmd][n-1] == 'z'
      op2 = $z.to_s
    elsif command_array[cmd][n-1] == 'w'
      op2 = $w.to_s
    else
      for i in (command_array[cmd].to_s.rindex(operator) + 1)..n-1
        op2 += command_array[cmd][i]
      end

    end

    expression = op1 + operator + op2
    output = eval(expression).to_f

    if command_array[cmd][0] == 'x'
      $x = output
    elsif command_array[cmd][0] == 'y'
      $y = output
    elsif command_array[cmd][0] == 'z'
      $z = output
    elsif command_array[cmd][0] == 'w'
      $w = output
    end
  end
end

#class for expression type 3 (id = constant)
class ExpressionType3 < ExpressionType12

  def expand(command_array,cmd)
    l=command_array[cmd]
    n=l.length
    sub=l[2..n-1]
    temp = eval(sub).to_f
    if(l[0]==='x')
      $x=temp
    end
    if(l[0]==='y')
      $y=temp
    end
    if(l[0]==='z')
      $z=temp
    end
    if(l[0]==='w')
      $w=temp
    end
  end
end

#class definition for expression type 4(. id ? go int)
class ExpressionType4 < ExpressionType3
  def expand(command_array,cmd)

    id = -1
    n = command_array[cmd].length
    if command_array[cmd][0] == 'x'
      id = $x
    elsif command_array[cmd][0] == 'y'
      id = $y
    elsif command_array[cmd][0] == 'z'
      id = $z
    elsif command_array[cmd][0] == 'w'
      id = $w
    end

    jumpid = ''

    if (id!=0)
      for i in 2..n-1
        jumpid += command_array[cmd][i]
      end
      jump_num = eval(jumpid)-1
      puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
      puts "JUMP to #{jump_num+1}"
      return jump_num
    else
      puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
      return cmd+1
    end

  end
end

#controller class
class CalculatorController

  #registers
  $x=0.0
  $y=0.0
  $w=0.0
  $z=0.0

  #Class instance initializations as class variables
  @@pc1 = CalculatorController.new
  @@t12 = ExpressionType12.new
  @@t3  = ExpressionType3.new
  @@t4  = ExpressionType4.new
  @@t   = InstructionAbstract.new
  @@type=Array.new

  #function to clean the input file
  def validateFile(inp_array)
    array_2 = Array.new
    itr = 0
    temp = Array.new
    while itr < inp_array.length
      temp = inp_array[itr]
      num = temp.length
      idx = temp.rindex(":")
      array_2[itr]=temp[(idx+1)..(num-3)]
      array_2[itr] = array_2[itr].to_s.gsub(" ", "")
      itr += 1
      if inp_array[itr] == 'end'
        break
      end
    end
    return array_2
  end

  #function to print the possible commands
  def printCommands
    puts "Welcome to Programmable Calculator by Nikita Thakur! \n"
    puts "Please select one of the below options:\n"
    puts "r : run entire pc_input.txt file \n"
    puts "s : execute line from pc_input.txt\n"
    puts "x : exit"
  end

  $cmd = 0
  #entry point to the calculator
  def inputLoop

    printCommands
    puts 'Your input:'
    input = gets.chomp
    instructions = Array.new
    instructions = IO.readlines("pc_input.txt")

    clean_array = validateFile(instructions)


    #determining the type of each expression as 1,2,3 or 4
    i=0
    while(i<clean_array.length)
      @@type[i]= @@t.InsType(clean_array[i])
      i+=1
    end

    if input == 'r'
      if $cmd <= 100
        puts "Executing pc_input.txt commands"
        $cmd = 0
        while($cmd < clean_array.length)
          if(@@type[$cmd]===3)
            @@t3.expand(clean_array,$cmd)
            puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
            $cmd+=1
          end
          if(@@type[$cmd]===1 or @@type[$cmd]===2)
            @@t12.expand(clean_array,$cmd)
            puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
            $cmd+=1
          end
          if (@@type[$cmd]===4)
            $cmd = @@t4.expand(clean_array,$cmd)
          end
        end
      end
      @@pc1.inputLoop
    end

    if input == 's'
      if $cmd <= clean_array.length
        if(@@type[$cmd]===1 or @@type[$cmd]===2)
          @@t12.expand(clean_array,$cmd)
          puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
          $cmd+=1
        elsif (@@type[$cmd]===3)
          @@t3.expand(clean_array,$cmd)
          puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
          $cmd+=1

        elsif (@@type[$cmd]===4)
          $cmd = @@t4.expand(clean_array,$cmd)
          puts " After executing line #{$cmd+1} : x=#{$x} , y=#{$y} , w=#{$w} , z=#{$z}\n"
        end
      @@pc1.inputLoop
      else
        puts "No more instructions left in the file. Please exit and begin a new calculator session."
      end
    end

    if input == 'x'
      puts "Quitting programmable calculator. Bye!"
    end

  end
end

pc = CalculatorController.new
pc.inputLoop