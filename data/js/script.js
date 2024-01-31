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
        for(let i = 1; i <= data.NUMBER_OF_SLAVES; i++)
        {
          var propertyName = "voltage" + i;
          document.getElementById("voltage" + i).textContent = data[propertyName];
          var propertyName = "temperature" + i;
          document.getElementById("temperature" + i).textContent = data[propertyName];

        }
        document.getElementById("voltage1").textContent = data.voltage1.toFixed(2);
        document.getElementById("temperature1").textContent = data.temperature1.toFixed(2);
        setColorBasedOnValue(data.voltage1, "voltage1");
        setColorBasedOnValue(data.temperature1, "temperature1");
        // Repeat for other cells
      })
      .catch(error => {
        console.error("Fetch error:", error);
      });
  }

  function setColorBasedOnValue(value, elementId) {
    const element = document.getElementById(elementId);
    // Customize these conditions based on your requirements
    if (value < 2.5) {
      element.parentElement.style.backgroundColor = "#FFCDD2"; // Light red
    } else if (value >= 2.5 && value < 3.5) {
      element.parentElement.style.backgroundColor = "#FFF9C4"; // Light yellow
    } else {
      element.parentElement.style.backgroundColor = "#C8E6C9"; // Light green
    }
  }

  updateMeasuredValues();
  setInterval(updateMeasuredValues, 1000);