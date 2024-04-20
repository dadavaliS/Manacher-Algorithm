def preprocess_string(s):
    processed = '^'
    for c in s:
        processed += '#' + c
    processed += '#$'
    return processed

def manacher(s):
    processed = preprocess_string(s)
    n = len(processed)
    P = [0] * n
    center = right = 0
    
    for i in range(1, n - 1):
        mirror = 2 * center - i
        
        if i < right:
            P[i] = min(right - i, P[mirror])
        
        while processed[i + 1 + P[i]] == processed[i - 1 - P[i]]:
            P[i] += 1
        
        if i + P[i] > right:
            center = i
            right = i + P[i]
    
    max_len = max(P)
    center_index = P.index(max_len)
    
    return s[(center_index - 1 - max_len) // 2 : (center_index - 1 + max_len) // 2 + 1]

def main():
    file_path = "input.txt"
    try:
        with open(file_path, "r") as inputFile:
            for line in inputFile:
                inputString = line.strip()
                result = manacher(inputString)
                print("Longest palindromic substring for '{}': {}".format(inputString, result))
    except FileNotFoundError:
        print(f"File '{file_path}' not found.")

if __name__ == "__main__":
    main()
