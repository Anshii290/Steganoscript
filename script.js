// script.js

// Tab switching logic
document.querySelectorAll('.tab-btn').forEach((btn) => {
    btn.addEventListener('click', function () {
      document.querySelector('.tab-btn.active').classList.remove('active');
      this.classList.add('active');
  
      const target = this.getAttribute('data-target');
      document.querySelectorAll('.tab-content').forEach((tab) => {
        tab.style.display = tab.id === target ? 'block' : 'none';
      });
    });
  });
  
  // Encoding logic
  document.getElementById('encodeBtn').addEventListener('click', () => {
    const plainText = document.getElementById('plainText').value;
    const binaryMessage = document.getElementById('binaryMessage').value;
    const method = document.getElementById('encodingMethod').value;
  
    let encodedText = '';
    if (method === 'selective') {
      encodedText = selectiveHiding(plainText, binaryMessage);
    } else if (method === 'whitespace') {
      encodedText = whitespaceHiding(plainText, binaryMessage);
    }
    document.getElementById('encodedText').value = encodedText;
  });
  
  // Decoding logic
  document.getElementById('decodeBtn').addEventListener('click', () => {
    const encodedInput = document.getElementById('encodedInput').value;
    const method = document.getElementById('decodingMethod').value;
  
    let decodedText = '';
    if (method === 'selective') {
      decodedText = decodeSelective(encodedInput);
    } else if (method === 'whitespace') {
      decodedText = decodeWhitespace(encodedInput);
    }
    document.getElementById('decodedText').value = decodedText;
  });
  
  // Selective Hiding Encoding
  function selectiveHiding(plainText, binaryMessage) {
    let encoded = '';
    let binaryIndex = 0;
  
    for (let char of plainText) {
      if (/[a-zA-Z]/.test(char) && binaryIndex < binaryMessage.length) {
        encoded += binaryMessage[binaryIndex] === '1' ? char.toUpperCase() : char.toLowerCase();
        binaryIndex++;
      } else {
        encoded += char;
      }
    }
    if (binaryIndex < binaryMessage.length) {
      alert('Plain text is too short to encode the entire binary message.');
      return '';
    }
    return encoded;
  }
  
  // Selective Hiding Decoding
  function decodeSelective(encodedText) {
    return [...encodedText].reduce((binary, char) => {
      if (/[a-zA-Z]/.test(char)) binary += char === char.toUpperCase() ? '1' : '0';
      return binary;
    }, '');
  }
  
  // Whitespace Encoding
  function whitespaceHiding(plainText, binaryMessage) {
    let encoded = '';
    let binaryIndex = 0;
  
    for (let char of plainText) {
      encoded += char;
      if (binaryIndex < binaryMessage.length) {
        encoded += binaryMessage[binaryIndex] === '1' ? '  ' : ' ';
        binaryIndex++;
      }
    }
    if (binaryIndex < binaryMessage.length) {
      alert('Plain text is too short to encode the entire binary message.');
      return '';
    }
    return encoded;
  }
  
  // Whitespace Decoding
  function decodeWhitespace(encodedText) {
    return encodedText.split(/[^ ]/).reduce((binary, space) => {
      if (space === ' ') binary += '0';
      else if (space === '  ') binary += '1';
      return binary;
    }, '');
  }
  