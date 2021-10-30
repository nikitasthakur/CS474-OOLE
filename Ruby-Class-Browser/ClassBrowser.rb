class ClassBrowser
  #Class Variables

  @@Current_Class = ClassBrowser.new

  @@ListOfSubClasses = []



  def initialize
    puts 'Ruby Class browser welcomes you.'
    @input = ''
  end

  #Merge Sort Implementation
  def mergeHelper(l,r)

    sortedStorage = []

    while !l.empty? && !r.empty?
      if(l[0] < r[0])
        sortedStorage.push(l.shift)
      else
        sortedStorage.push(r.shift)
      end
    end

    sortedStorage.concat(l,r)
    return sortedStorage
  end

  def mergeSort(array)
    if(array == nil)
      return []
    end
    if(array.length <= 1)
      return array
    else
      midpoint = array.length/2
      half1 = mergeSort(array.slice(0...midpoint))
      half2 = mergeSort(array.slice(midpoint...array.length))
      mergeHelper(half1,half2)
    end
  end

  #function to print the enumerated list of objects in the arrayay
  def getEnumeratedList(array)
    iter = 0
    while iter < array.length
      puts '  ' + iter.to_s + '  ' + array[iter].to_s
      iter += 1
    end
    if(array.length == 0)
      puts '  <No items present in the list>'
    end

  end

  #converting objects to string so that they can be compared by the mergeSort function
  def ObjectToStringArray(array)
    iter = 0
    string_array = []
    while iter < array.length
      hold = array[iter].to_s
      if(hold != "")
        if(hold[0] != "#")
          if(!hold.include? "::")
            string_array.append(hold)
          end
        end
      end
      iter += 1
    end
    return string_array
  end

  def printCommands
    puts 'Listed below are the available commands:-'
    puts 's: Display the superclass information.'
    puts 'u: (n) n-th subclass'
    puts 'm: list of public class methods'
    puts 'c: (string) Class name input'
    puts 'q: quit'
  end


  # @return [nil]
  def entryPoint
    defaultClass = @@Current_Class

    puts '1. Current class: ' + defaultClass.class.name

    puts '2. Superclass of Current Class: ' + defaultClass.class.superclass.to_s

    puts '3. List of subclasses of the current class'
    subclasses = (ObjectSpace.each_object(Class).select { | kl | kl < defaultClass.class})
    subclasses = ObjectToStringArray(subclasses)
    subclasses = mergeSort(subclasses)
    if(subclasses == nil)
      subclasses = []
    end
    getEnumeratedList(subclasses)
    @@ListOfSubClasses = subclasses

    puts '4. List of methods'
    methods = defaultClass.class.instance_methods(false)
    methods = ObjectToStringArray(methods)
    methods = mergeSort(methods)
    if(methods == nil)
      methods = []
    end

    getEnumeratedList(methods)

    puts '5. List of instance variables:'

    puts defaultClass.instance_variables.to_s



  end

  def optionS
    if(@@Current_Class.class.name == "Object")
      puts 'NO superclasses above this point.'
    else
      temp =  @@Current_Class.class.superclass.to_s
      temp = Kernel.const_get(temp).new
      @@Current_Class = temp

      entryPoint
    end


  end


  def optionU(input)

    if(input.length < 3)
      puts 'Cannot resolve the input command. Please try Again.'
    else
      temp = input[2..input.length-1]
      temp2 = Integer(temp)

      if(temp2.to_s == temp)


        if (temp2 >= 0 && temp2 <= @@ListOfSubClasses.length)
          newClass = @@ListOfSubClasses[temp2]
          begin
            newClassObj = Kernel.const_get(newClass).new
            @@Current_Class = newClassObj

            entryPoint
          rescue
            puts 'Could not create object as it required parameters to be made. Please try again.'
          end

        else
          puts 'Index was out of bounds. Please try again.'
        end
      else
        puts 'No number detected. Please try again'
      end

    end

  end


  def optionC(input)
    if(input.length < 3)
      puts 'Cannot resolve the input command. Please try Again.'
    else
      newClass = input[2..input.length-1]

      begin
        newClassObj = Kernel.const_get(newClass).new

        @@Current_Class = newClassObj

        entryPoint
      rescue
        puts 'Could not create object as class doesn\'t exist, or input requires more parameters. Please try again.'
      end
    end


  end

  def optionM(input)

    methods = @@Current_Class.class.public_methods(false)
    methods = ObjectToStringArray(methods)
    methods = mergeSort(methods)
    if(methods == nil)
      methods = []
    end
    puts 'List of Public Methods of the current class'
    getEnumeratedList(methods)
    entryPoint
  end

  def menu
    entryPoint
    printCommands
    puts 'Your input:'
    input = gets.chomp
    while input != 'q'

      if input == 's'
        optionS
      elsif input[0] == 'u'
        optionU(input)

      elsif input == 'm'
        optionM(input)

      elsif input[0] == 'c'
        optionC(input)

      elsif input == 'q'
        exit
      else
        puts 'Unknown input command.Please try again.'
      end
      printCommands
      puts 'Your input:'
      input = gets.chomp
    end

  end

end

classbrowser = ClassBrowser.new
classbrowser.menu