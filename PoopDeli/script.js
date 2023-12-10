const bread = 's!!!!!!!!!!!!!!!!!!!!!k!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!8!!!!!!!!!!!X!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Z!!!!!!!!!!!!!!!!!!!!!!!!!!B!!!!!!!!!!!!!!!!!!!!!!!!a!!!!!!!!!!!!!!!!O!!!!!!!!!!!!!!!!!!!!!!!!!!!h!!!!!!!!!!!!!!!!!!!!!!!g!!!!!!!!!!!!!!!!B!!!!!!!!!!!!!!!!!!!!!!b!!!!!!!!!!!!!!!!!!!!!!!!!!!!J!!!!!!!!!!!C!!!!!!!!!!!!5!!!!!!!!!!!!e!!!!!!!!!!!!!!!!!!!!!!!!X!!!!!!!!!!!!!!!!!!!!!!!!C!!!!!!!!!!!!!!!!!!!!!o!!!!!!!!!!!!!!!!!!!!!u!!!!!!!!!!!v!!!!!!!!!!!!!!!!!!!!!!!!!!B!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!T!!!!!!!!!!!!!!!!!!3!!!!!!!!!!!!!!!!!!!!!!!!!!B!!!!!!!!!!!!l!!!!!!!!!!!!!!!!!!!b!!!!!!!!!!!!!!!!!!!!k!!!!!!!!!!!!!!!!!!!!!!!!!!!F!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!J!!!!!!!!!!!!!!!!!!!!K!!!!!!!!!!!!!!!!!!!!!!!!!!!K!!!!!!!!!!!!!!!!!!!D!!!!!!!!!!!!!!!!!!!!!Q!!!!!!!!!!!!!!!!!!!!!!!!!!!!s!!!!!!!!!!!!!!!!!!G!!!!!!!!!!!!!!!!!!!!!!!h!!!!!!!!!!!!!!!!!!!!!!!!!!!Z!!!!!!!!!!!!!!!!!!!!!!!!S!!!!!!!!!!!!!!!!!!!!!!!!!!!!!c!!!!!!!!!!!G!!!!!!!!!!!!!!!!!!!a!!!!!!!!!!!!!!!!!!M!!!!!!!!!!!!!!!!!!!!!!!Y!!!!!!!!!!!!!!!!!!!!G!!!!!!!!!!p!!!!!!!!!!!!!!N!!!!!!!!!!!!!!!!H!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!M!!!!!!!!!!!!t!!!!!!!!!!!!!!!!!!!!!!!!!!!';
const poop = bread.replace(/!/g, "")
const chatHistory = [];

function sendMessage() {
    const inputField = document.getElementById('userInput');
    const userMessage = inputField.value.trim();
    if (userMessage) {
        inputField.value = '';
        updateChat('You', userMessage, 'user');
        chatHistory.push({ role: 'user', content: userMessage });
        fetchResponse(userMessage);
    }
}

function fetchResponse(message) {
    updateChat('Greg', 'Thinking...', 'ai-loading');
    fetch('https://api.openai.com/v1/engines/gpt-3.5-turbo/completions', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + poop
        },
        body: JSON.stringify({
            prompt: message,
            max_tokens: 150
        })
    })
    .then(response => response.json())
    .then(data => {
        const chatDiv = document.getElementById('chat');
        chatDiv.removeChild(chatDiv.lastChild); // remove loading message
        const aiMessage = data.choices[0].text.trim();
        updateChat('Greg', aiMessage, 'ai');
        chatHistory.push({ role: 'assistant', content: aiMessage });
    })
    .catch(error => {
        console.error('Error:', error);
        updateChat('Greg', 'Error getting response.', 'ai');
    });
}

function updateChat(sender, message, className) {
    const chatDiv = document.getElementById('chat');
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('message', className);
    messageDiv.innerHTML = `<strong>${sender}:</strong> ${message}`;
    chatDiv.appendChild(messageDiv);
    chatDiv.scrollTop = chatDiv.scrollHeight; // Auto-scroll to the latest message
}