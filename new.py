import openai

# Set up your OpenAI API key
openai.api_key = "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"

def generate_cover_text(prompt, max_tokens=100):
    """
    Generate plausible cover text using an LLM.
    """
    try:
        response = openai.ChatCompletion.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": prompt}
            ],
            max_tokens=max_tokens
        )
        return response['choices'][0]['message']['content'].strip()
    except Exception as e:
        print(f"Error generating cover text: {e}")
        return None

def embed_message(cover_text, secret_message):
    """
    Embed the secret message into the cover text using whitespace encoding.
    """
    binary_message = ''.join(format(ord(char), '08b') for char in secret_message)
    embedded_text = []
    for i, char in enumerate(cover_text):
        if i < len(binary_message) and binary_message[i] == '1':
            embedded_text.append(char + ' ')  # Add a space for binary '1'
        else:
            embedded_text.append(char)  # Keep it as is for binary '0'
    return ''.join(embedded_text)

def extract_message(embedded_text):
    """
    Extract the hidden secret message from the embedded text.
    """
    binary_message = ''
    for i in range(len(embedded_text) - 1):
        if embedded_text[i] != ' ' and embedded_text[i + 1] == ' ':
            binary_message += '1'
        elif embedded_text[i] != ' ':
            binary_message += '0'
    secret_message = ''.join(chr(int(binary_message[i:i+8], 2)) for i in range(0, len(binary_message), 8))
    return secret_message

def main():
    print("--- Stegano Script with LLM Integration ---")

    # Step 1: Generate Cover Text
    prompt = "Write a professional email about completing a project on time."
    cover_text = generate_cover_text(prompt)
    if not cover_text:
        print("Failed to generate cover text. Exiting.")
        return

    print("Generated Cover Text:")
    print(cover_text)

    # Step 2: Embed Secret Message
    secret_message = input("Enter the secret message to hide: ")
    embedded_text = embed_message(cover_text, secret_message)

    print("\nEmbedded Text:")
    print(embedded_text)

    # Step 3: Extract Secret Message
    extracted_message = extract_message(embedded_text)
    print("\nExtracted Secret Message:")
    print(extracted_message)

if __name__ == "__main__":
    main()

