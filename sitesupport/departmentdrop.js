/*
 * Javacript for the Department List Dropdown
 */

/* jshint browser: true */
/* jshint -W097 */
/* globals apiRequest */

var departmentDropdown = (function(options) {
  'use strict';

  var settings = Object.assign(
    {
      div: null,
      filter: null,
    }, options);

  return {
    options: function(opts) {
      settings = Object.assign(settings, opts);
    },

    addDepartments: function(response) {
      var data = JSON.parse(response.responseText);
      var list = [];
      data.data.forEach(function(dept) {
        if (settings.filter === null || settings.filter(dept)) {
          list.push(dept);
        }
      });
      list.sort(function(a, b) {
        return a.name.toLowerCase().localeCompare(b.name.toLowerCase());
      });
      var select = document.getElementById('department_dropdown_select');
      list.forEach(function(dept) {
        var option = document.createElement('option');
        option.text = dept.name;
        option.value = dept.id;
        select.add(option);
      });
    },

    build: function(opts) {
      settings = Object.assign(settings, opts);
      var dom = document.getElementById(settings.div);
      var select = document.createElement('SELECT');
      select.id = 'department_dropdown_select';
      select.classList.add('UI-input');
      dom.appendChild(select);
      apiRequest('GET', '/department', 'max_results=all')
        .then(departmentDropdown.addDepartments)
        .catch(function(response) {
          select.value = response.responseText;
        });
    }
  };
})();
