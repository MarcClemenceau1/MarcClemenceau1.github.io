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
    // Replace VERCEL_URL with your actual Vercel deployment URL
    const vercelUrl = 'https://us-west1-echo-386517.cloudfunctions.net/TalkToGreg';

    fetch(vercelUrl, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            messages: [
                {
                    role: "system",
                    content: "You are a helpful assistant."
                },
                {
                    role: "user",
                    content: message
                }
            ]
        })
    })
    .then(response => response.json())
    .then(data => {
        const aiMessage = data.choices[0].message.content;
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