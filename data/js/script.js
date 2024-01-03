function updateMeasuredValues() {
    fetch("/api/measured-values")
        .then(response => {
            if (!response.ok) {
                throw new Error("Network response was not ok");
            }
            return response.json();
        })
        .then(data => {
            // Update the measured values on your webpage using JavaScript
            document.getElementById("voltage1").textContent = data.voltage1.toFixed(2);
            document.getElementById("temperature1").textContent = data.temperature1.toFixed(2);
        })
        .catch(error => {
            console.error("Fetch error:", error);
        });
}


updateMeasuredValues();
setInterval(updateMeasuredValues, 1000); 