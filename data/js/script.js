function updateMeasuredValues() {
  return new Promise((resolve, reject) => {
    fetch("/api/measured-values")
      .then(response => {
        if (!response.ok) {
          throw new Error("Network response was not ok");
        }
        return response.json();
      })
      .then(data => {
        // Update the measured values on your webpage using JavaScript
        resolve(data);
        // Repeat for other cells
      })
      .catch(error => {
        console.error("Fetch error:", error);
        reject();
      });
  });

}

const renderTable = (number_of_slaves) => {
  const $table = $('#batteryDataTableBody');
  for (let i = 0; i < number_of_slaves; ++i) {
    const $tableRow = $('<tr>').attr({ id: 'cell' + (i + 1) });
    const $tableHead = $('<th>').attr({ scope: 'row' }).text(i + 1);
    const $voltage = $('<td>').attr({ id: 'voltage' + (i + 1) });
    const $temperature = $('<td>').attr({ id: 'temperature' + (i + 1) });
    const $status = $('<td>').attr({ id: 'status' + (i + 1) });

    $tableRow
      .append($tableHead)
      .append($voltage)
      .append($temperature)
      .append($status);
    $table.append($tableRow);
  }
}

const updateTable = data => {
  for (let i = 1; i <= data.NUMBER_OF_SLAVES; i++) {
    $("#voltage" + i).text(data["voltage" + i].toFixed(2));
    $("#temperature" + i).text(data["temperature" + i]);
  }
  

  // setColorBasedOnValue(data.voltage1, "voltage1");
  // setColorBasedOnValue(data.temperature1, "temperature1");
}

$(() => {
  updateMeasuredValues().then(data => {
    renderTable(data.NUMBER_OF_SLAVES);
    updateTable(data);
    setInterval(updateMeasuredValues, 1000);
  }).catch(err => {
    console.log(err);
    $('body').append($('<p>').text("Error"));
  });
})
