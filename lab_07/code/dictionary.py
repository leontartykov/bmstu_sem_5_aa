class Dictionary():
    def __init__(self):
        self.dictionary = dict()
        self.sorted_dictionary = dict()
        self.segment_dictionary = list()
        self.len = 0

    def parser(self, file_name_in):
        with open(file_name_in, "r") as file:
            for line in file:
                words = self.find_words(line)
                self.add_words_to_dictionary(words)
                self.sorted_dictionary = {k: self.dictionary[k] for k in sorted(self.dictionary)}

        segment_digits = dict()
        segment_letters = dict()
        letter = 'a'
        for key, value in self.sorted_dictionary.items():
            if key[0].isdigit():
                segment_digits.update({key:value})
            else:
                if key[0] != letter:
                    letter = key[0]
                    self.segment_dictionary.append(segment_letters)
                    segment_letters = dict()
                else:
                    segment_letters.update({key:value})
        self.segment_dictionary.append(segment_digits)

    def output(self):
        print(f"self.len = {self.len}")
        len_segments = len(self.segment_dictionary)
        #print(self.sorted_dictionary)
        #for i in range(len_segments):
           #print(self.segment_dictionary[i])

    def find_words(self, line):
        list_words = list()
        start_word = 0; end_word = 0
        line = line.split()

        for i in range(len(line)):
            len_word = len(line[i]); word = ''
            start_word = 0; end_word = 0
            if len_word == 1 and line[i].isalpha() == True:
                word = line[i]
            elif len_word > 1:
                is_start_find = False; is_end_find = True
                for j in range(len_word):
                    if line[i][j].isalpha():
                        if is_start_find == False:
                            start_word = j
                            is_start_find = True
                        else:
                            end_word = j
                word = line[i][start_word:end_word+1]
            if word != '':
                list_words.append(word)                
        return list_words

    def add_words_to_dictionary(self, words:list):
        if words != []:
            len_words = len(words)
            for i in range(len_words):
                word = words[i].lower() 
                if self.is_word_in_dictonary(word) == False:
                    self.dictionary.update({word:1})
                    self.len += 1

    def is_word_in_dictonary(self, word):
        is_find = False
        for key in self.dictionary.keys():
            if is_find == True:
                break
            if key == word:
                self.dictionary[key] += 1
                is_find = True
                break
        return is_find

    def find_by_full_search(self, word):
        is_find_key = False
        value = 0
        count_compares = 0
        for key in self.dictionary.keys():
            if is_find_key == True:
                break
            if key == word:
                is_find_key = True
                value = self.dictionary[key]
            count_compares += 1
        return value, count_compares

    def find_by_binary_search(self, word, dictionary=None):
        if dictionary == None:
            dictionary = self.sorted_dictionary
            left = 0; right = self.len - 1
        else:
            left = 0; right = len(dictionary) - 1

        is_find = False; value = 0
        list_dictionary = list(dictionary) 
        count_compares = 0
        while is_find == False and right >= left:
            middle = (left + right) // 2
            key = list_dictionary[middle]
            if key == word:
                is_find = True
                value = dictionary.get(key)
            elif key > word:
                right = middle - 1
            else:
                left = middle + 1
            count_compares += 1
        return value, count_compares

    def find_by_segment_search(self, word):
        count_compares = 0
        count_segments = len(self.segment_dictionary)
        result = 0; count_companies = 0
        for i in range(count_segments):
            if word[0] == list(self.segment_dictionary[i])[0][0]:
                result, binary_search_compares = self.find_by_binary_search(word, self.segment_dictionary[i])
                count_compares += binary_search_compares
                break
        return result, count_compares