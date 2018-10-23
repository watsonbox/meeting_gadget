function doGet(e) {
  var currentTime = new Date();
  var result = ("0" + currentTime.getHours()).slice(-2)   + ":" +
               ("0" + currentTime.getMinutes()).slice(-2) + ":" +
               ("0" + currentTime.getSeconds()).slice(-2);
  Logger.log(result);
  return ContentService.createTextOutput(result);
}
