$(document).ready(function(){
	let sum = 0;
	var list = [];
	var subTotal = document.getElementById("lista");
	//-----------------------------
	var node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15;
	//-----------------------------
	var nodePrice1, nodePrice2, nodePrice3, nodePrice4, nodePrice5, nodePrice6, nodePrice7, nodePrice8, nodePrice9, nodePrice10, nodePrice11, nodePrice12, nodePrice13, nodePrice14, nodePrice15;
	//-----------------------------
	var itemNode1, itemNode2, itemNode3, itemNode4, itemNode5, itemNode6, itemNode7, itemNode8, itemNode9, itemNode10, itemNode11, itemNode12, itemNode13, itemNode14, itemNode15;
	//-----------------------------
	var valueNode1, valueNode2, valueNode3, valueNode4, valueNode5, valueNode6, valueNode7, valueNode8, valueNode9, valueNode10, valueNode11, valueNode12, valueNode13, valueNode14, valueNode15;
	//-----------------------------
	var dia1, dia2, dia3, dia4, dia5, dia6, dia7, dia8, dia9, dia10, dia11, dia12, dia13, dia14, dia15;
	//-----------------------------
	var diaNode1, diaNode2, diaNode3, diaNode4, diaNode5, diaNode6, diaNode7, diaNode8, diaNode9, diaNode10, diaNode11, diaNode12, diaNode13, diaNode14, diaNode15;
	//-----------------------------
	var price = []; 
	price.length = 14;
	for (var i = 0; i < price.length; i++) {
		price[i] = 0;
	}
	var totalPrice = 0;
	var selected = false, selected1 = false, selected2 = false, selected3 = false, selected4 = false, selected5 = false, selected6 = false,  selected7 = false, selected8 = false, selected9 = false, selected10 = false, selected11 = false, selected12 = false, selected13 = false, selected14 = false;
	var selectedDay1 = false, selectedDay2 = false, selectedDay3 = false, selectedDay4 = false, selectedDay5 = false, selectedDay6 = false, selectedDay7 = false,  selectedDay8 = false, selectedDay9 = false, selectedDay10 = false, selectedDay11 = false, selectedDay12 = false, selectedDay13 = false, selectedDay14 = false, selectedDay15 = false;
	var stateBool = false;
	var displayElement = false;
	var displayElementTercero = false;	
	var displayHeader = false;
	var stateBoolTercero = false;

	let stickyItemsTab = document.querySelector(".stickyItemsTable");
	let navBar = document.querySelector("#navigation"); 

	stickyItemsTab? stickyItemsTab.style.top = navBar.scrollTop + navBar.offsetHeight + "px" : console.log("Element can't be read"); 

//-----------------------------------------------------------------------------------------	
  	$('.iqdropdown').iqDropdown({
  		 // max total items
		maxItems: Infinity,
		// min total items
		minItems: 0,
		// text to show on the dropdown
		selectionText: 'item',
		// text to show for multiple items
		textPlural: 'items',
		// buttons to increment/decrement
		controls: {
			position: 'right',
			displayCls: 'iqdropdown-item-display',
			controlsCls: 'iqdropdown-item-controls',
			counterCls: 'counter'
		},
		onChange: function(id, count, totalItems) {
			if (count >= 1 && displayHeader === false) {
				document.getElementById("pItem").style.display = "block";
				document.getElementById("pCantidad").style.display = "block";
				document.getElementById("pDias").style.display = "block";
				document.getElementById("pValorU").style.display = "block";
				document.getElementById("pSubtotal").style.display = "block";
				displayHeader = true;
			}
			else if (count === 0 && displayHeader === true) {
				document.getElementById("pItem").style.display = "none";
				document.getElementById("pCantidad").style.display = "none";
				document.getElementById("pDias").style.display = "none";
				document.getElementById("pValorU").style.display = "none";
				document.getElementById("pSubtotal").style.display = "none";
				displayHeader = false;	
			}
			if (id === "itemDias1") {
				dia1 = Number($("#dias1").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay1 == false) {
					diaNode1 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode1);
					diaNode1.innerHTML = Number($("#dias1").attr('data-value'))*Number(count);
					selectedDay1 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode1);
					selectedDay1 = false;
				}
				else {
					diaNode1.innerHTML = Number($("#dias1").attr('data-value'))*Number(count);
				}
				
				if (nodePrice1) {
					nodePrice1.innerHTML = Number($("#itm1").attr('data-value'))*dia1;
				}
				price[0] = +Number($("#itm1").attr('data-value'))*dia1;
			}
			if (id === "item1") { 
				//-------------------------------------------------------------------
				if (count == 1 && selected == false) {
					itemNode1 = document.createElement("LI");
					node1 = document.createElement("LI");
					valueNode1 = document.createElement("LI");
					nodePrice1 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode1);                 
					document.getElementById("lista2").appendChild(node1);
					document.getElementById("valorU").appendChild(valueNode1);
					document.getElementById("lista3").appendChild(nodePrice1);
					itemNode1.innerHTML = $("#itm1").html();
					node1.innerHTML = count;
					valueNode1.innerHTML = Number($("#itm1").attr('data-value'));
					nodePrice1.innerHTML = Number($("#itm1").attr('data-value'))*count*dia1;
					selected = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode1);
					document.getElementById("lista2").removeChild(node1);
					document.getElementById("valorU").removeChild(valueNode1);
					document.getElementById("lista3").removeChild(nodePrice1);
					selected = false;
				}
				else {
					nodePrice1.innerHTML = Number($("#itm1").attr('data-value'))*count*dia1;
					node1.innerHTML = count;
				}
					
				price[0] = +Number($("#itm1").attr('data-value'))*count*dia1;
				//--------------------------------------------------------------------
			}
			if (id === "itemDias2") {
				dia2 = Number($("#dias2").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay2 == false) {
					diaNode2 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode2);
					diaNode2.innerHTML = Number($("#dias2").attr('data-value'))*Number(count);
					selectedDay2 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode2);
					selectedDay2 = false;
				}
				else {
					diaNode2.innerHTML = Number($("#dias2").attr('data-value'))*Number(count);
				}
				if (nodePrice2) {
					nodePrice2.innerHTML = Number($("#itm2").attr('data-value'))*dia2;
				}
				price[1] = +Number($("#itm2").attr('data-value'))*dia2;
			}

			if (id === "item2") {
				if (count == 1 && selected1 == false) {
					itemNode2 = document.createElement("LI");
					node2 = document.createElement("LI");
					valueNode2 = document.createElement("LI");
					nodePrice2 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode2);                 
					document.getElementById("lista2").appendChild(node2);
					document.getElementById("lista3").appendChild(nodePrice2);
					document.getElementById("valorU").appendChild(valueNode2);
					itemNode2.innerHTML = $("#itm2").html();
					node2.innerHTML = count;
					valueNode2.innerHTML = Number($("#itm2").attr('data-value'));
					nodePrice2.innerHTML = Number($("#itm2").attr('data-value'))*count*dia2;
					selected1 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode2);
					document.getElementById("lista2").removeChild(node2);
					document.getElementById("valorU").removeChild(valueNode2);
					document.getElementById("lista3").removeChild(nodePrice2);
					selected1 = false;
				}
				else {
					node2.innerHTML = count;
					nodePrice2.innerHTML = Number($("#itm2").attr('data-value'))*count*dia2;
				}
				price[1] = +Number($("#itm2").attr('data-value'))*count*dia2;
			}

			if (id === "itemDias3") {
				dia3 = Number($("#dias3").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay3 == false) {
					diaNode3 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode3);
					diaNode3.innerHTML = Number($("#dias3").attr('data-value'))*Number(count);
					selectedDay3 = true;
				}
				else if (count == 0) {
						document.getElementById("diaList").removeChild(diaNode3);
						selectedDay3 = false;
					}
				else {
					diaNode3.innerHTML = Number($("#dias3").attr('data-value'))*Number(count);
				}
				if (nodePrice3) {
					nodePrice3.innerHTML = Number($("#itm3").attr('data-value'))*dia3;
				}
				price[2] = +Number($("#itm3").attr('data-value'))*dia3;
			}
			if (id === "item3") {
				if (count == 1 && selected2 == false) {
					itemNode3 = document.createElement("LI");
					node3 = document.createElement("LI");
					valueNode3 = document.createElement("LI");                 
					nodePrice3 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode3);
					document.getElementById("lista2").appendChild(node3);
					document.getElementById("valorU").appendChild(valueNode3);
					document.getElementById("lista3").appendChild(nodePrice3);
					itemNode3.innerHTML = $("#itm3").html(); 
					node3.innerHTML = count;
					valueNode3.innerHTML = Number($("#itm3").attr('data-value'));
					nodePrice3.innerHTML = Number($("#itm3").attr('data-value'))*count*dia3;
					selected2 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode3);
					document.getElementById("lista2").removeChild(node3);
					document.getElementById("valorU").removeChild(valueNode3);
					document.getElementById("lista3").removeChild(nodePrice3);
					selected2 = false;
				}
				else {
					node3.innerHTML = count;
					nodePrice3.innerHTML = Number($("#itm3").attr('data-value'))*count*dia3;
				}
				price[2] = +Number($("#itm3").attr('data-value'))*count*dia3;
			}

			if (id === "itemDias4") {
				dia4 = Number($("#dias4").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay4 == false) {
					diaNode4 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode4);
					diaNode4.innerHTML = Number($("#dias4").attr('data-value'))*Number(count);
					selectedDay4 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode4);
					selectedDay4 = false;
				}
				else {
					diaNode4.innerHTML = Number($("#dias4").attr('data-value'))*Number(count);
				}
				if (nodePrice4) {
					nodePrice4.innerHTML = Number($("#itm4").attr('data-value'))*dia4;
				}
				price[3] = +Number($("#itm4").attr('data-value'))*dia4;
			}
			if (id === "item4") {
				if (count == 1 && selected3 == false) {
					itemNode4 = document.createElement("LI");
					node4 = document.createElement("LI");
					valueNode4 = document.createElement("LI");                 
					nodePrice4 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode4);
					document.getElementById("lista2").appendChild(node4);
					document.getElementById("valorU").appendChild(valueNode4);
					document.getElementById("lista3").appendChild(nodePrice4);
					itemNode4.innerHTML = $("#itm4").html();
					node4.innerHTML = count;
					valueNode4.innerHTML = Number($("#itm4").attr('data-value'));
					nodePrice4.innerHTML = Number($("#itm4").attr('data-value'))*count*dia4;
					selected3 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode4);
					document.getElementById("lista2").removeChild(node4);
					document.getElementById("valorU").removeChild(valueNode4);
					document.getElementById("lista3").removeChild(nodePrice4);
					selected3 = false;
				}
				else {
					node4.innerHTML = count;
					nodePrice4.innerHTML = Number($("#itm4").attr('data-value'))*count*dia4;
				}
				price[3] = +Number($("#itm4").attr('data-value'))*count*dia4;
			}

			if (id === "itemDias5") {
				dia5 = Number($("#dias5").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay5 == false) {
					diaNode5 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode5);
					diaNode5.innerHTML = Number($("#dias5").attr('data-value'))*Number(count);
					selectedDay5 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode5);
					selectedDay5 = false;
				}
				else {
					diaNode5.innerHTML = Number($("#dias5").attr('data-value'))*Number(count);
				}
				if (nodePrice5) {
					nodePrice5.innerHTML = Number($("#itm5").attr('data-value'))*dia5;
				}
				price[4] = +Number($("#itm5").attr('data-value'))*dia5;
			}
			if (id === "item5") {
				if (count == 1 && selected4 == false) {
					itemNode5 = document.createElement("LI");
					node5 = document.createElement("LI");
					valueNode5 = document.createElement("LI");
					nodePrice5 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode5);                 
					document.getElementById("lista2").appendChild(node5);
					document.getElementById("valorU").appendChild(valueNode5);
					document.getElementById("lista3").appendChild(nodePrice5);
					itemNode5.innerHTML = $("#itm5").html();
					node5.innerHTML = count;
					valueNode5.innerHTML = Number($("#itm5").attr('data-value'));
					nodePrice5.innerHTML = Number($("#itm5").attr('data-value'))*count*dia5;
					selected4 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode5);
					document.getElementById("lista2").removeChild(node5);
					document.getElementById("valorU").removeChild(valueNode5);
					document.getElementById("lista3").removeChild(nodePrice5);
					selected4 = false;
				}
				else {
					node5.innerHTML = count;
					nodePrice5.innerHTML = Number($("#itm5").attr('data-value'))*count*dia5;
				}
				price[4] = +Number($("#itm5").attr('data-value'))*count*dia5;
			}

			if (id === "itemDias6") {
				dia6 = Number($("#dias6").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay6 == false) {
					diaNode6 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode6);
					diaNode6.innerHTML = Number($("#dias6").attr('data-value'))*Number(count);
					selectedDay6 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode6);
					selectedDay6 = false;
				}
				else {
					diaNode6.innerHTML = Number($("#dias6").attr('data-value'))*Number(count);
				}
				if (nodePrice6) {
					nodePrice6.innerHTML = Number($("#itm6").attr('data-value'))*dia6;
				}
				price[5] = +Number($("#itm6").attr('data-value'))*dia6;
			}
			if (id === "item6") {
				if (count == 1 && selected5 == false) {
					itemNode6 = document.createElement("LI");
					node6 = document.createElement("LI");
					valueNode6 = document.createElement("LI");                 
					nodePrice6 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode6);
					document.getElementById("lista2").appendChild(node6);
					document.getElementById("valorU").appendChild(valueNode6);
					document.getElementById("lista3").appendChild(nodePrice6);
					itemNode6.innerHTML = $("#itm6").html();
					node6.innerHTML = count;
					valueNode6.innerHTML = Number($("#itm6").attr('data-value'));
					nodePrice6.innerHTML = Number($("#itm6").attr('data-value'))*count*dia6;
					selected5 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode6);
					document.getElementById("lista2").removeChild(node6);
					document.getElementById("valorU").removeChild(valueNode6);
					document.getElementById("lista3").removeChild(nodePrice6);
					selected5 = false;
				}
				else {
					node6.innerHTML = count;
					nodePrice6.innerHTML = Number($("#itm6").attr('data-value'))*count*dia6;
				}
				price[5] = +Number($("#itm6").attr('data-value'))*count*dia6;
			}

			if (id === "itemDias7") {
				dia7 = Number($("#dias7").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay7 == false) {
					diaNode7 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode7);
					diaNode7.innerHTML = Number($("#dias7").attr('data-value'))*Number(count);
					selectedDay7 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode7);
					selectedDay7 = false;
				}
				else {
					diaNode7.innerHTML = Number($("#dias7").attr('data-value'))*Number(count);
				}
				if (nodePrice7) {
					nodePrice7.innerHTML = Number($("#itm7").attr('data-value'))*dia7;
				}
				price[6] = +Number($("#itm7").attr('data-value'))*dia7;
			}
			if (id === "item7") {
				if (count == 1 && selected6 == false) {
					itemNode7 = document.createElement("LI");
					node7 = document.createElement("LI");
					valueNode7 = document.createElement("LI");                 
					nodePrice7 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode7);
					document.getElementById("lista2").appendChild(node7);
					document.getElementById("valorU").appendChild(valueNode7);
					document.getElementById("lista3").appendChild(nodePrice7);
					itemNode7.innerHTML = $("#itm7").html();
					node7.innerHTML = count;
					valueNode7.innerHTML = Number($("#itm7").attr('data-value'));
					nodePrice7.innerHTML = Number($("#itm7").attr('data-value'))*count*dia7;
					selected6 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode7);
					document.getElementById("lista2").removeChild(node7);
					document.getElementById("valorU").removeChild(valueNode7);
					document.getElementById("lista3").removeChild(nodePrice7);
					selected6 = false;
				}
				else {
					node7.innerHTML = count;
					nodePrice7.innerHTML = Number($("#itm7").attr('data-value'))*count*dia7;
				}
				price[6] = +Number($("#itm7").attr('data-value'))*count*dia7;	
			}

			if (id === "itemDias8") {
				dia8 = Number($("#dias8").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay8 == false) {
					diaNode8 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode8);
					diaNode8.innerHTML = Number($("#dias8").attr('data-value'))*Number(count);
					selectedDay8 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode8);
					selectedDay8 = false;
				}
				else {
					diaNode8.innerHTML = Number($("#dias8").attr('data-value'))*Number(count);
				}
				if (nodePrice8) {
					nodePrice8.innerHTML = Number($("#itm8").attr('data-value'))*dia8;
				}
				price[7] = +Number($("#itm8").attr('data-value'))*dia8;
			}
			if (id === "item8") {
				if (count == 1 && selected7 == false) {
					itemNode8 = document.createElement("LI");
					node8 = document.createElement("LI");
					valueNode8 = document.createElement("LI");                 
					nodePrice8 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode8);
					document.getElementById("lista2").appendChild(node8);
					document.getElementById("valorU").appendChild(valueNode8);
					document.getElementById("lista3").appendChild(nodePrice8);
					itemNode8.innerHTML = $("#itm8").html();
					node8.innerHTML = count;
					valueNode8.innerHTML = Number($("#itm8").attr('data-value'));
					nodePrice8.innerHTML = Number($("#itm8").attr('data-value'))*count*dia8;
					selected7 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode8);
					document.getElementById("lista2").removeChild(node8);
					document.getElementById("valorU").removeChild(valueNode8);
					document.getElementById("lista3").removeChild(nodePrice8);
					selected7 = false;
				}
				else {
					node8.innerHTML = count;
					nodePrice8.innerHTML = Number($("#itm8").attr('data-value'))*count*dia8;
				}
				price[7] = +Number($("#itm8").attr('data-value'))*count*dia8;
			}

			if (id === "itemDias9") {
				dia9 = Number($("#dias9").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay9 == false) {
					diaNode9 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode9);
					diaNode9.innerHTML = Number($("#dias9").attr('data-value'))*Number(count);
					selectedDay9 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode9);
					selectedDay9 = false;
				}
				else {
					diaNode9.innerHTML = Number($("#dias9").attr('data-value'))*Number(count);
				}
				if (nodePrice9) {
					nodePrice9.innerHTML = Number($("#itm9").attr('data-value'))*dia9;
				}
				price[8] = +Number($("#itm9").attr('data-value'))*dia9;
			}
			if (id === "item9") {
				if (count == 1 && selected8 == false) {
					itemNode9 = document.createElement("LI");
					node9 = document.createElement("LI");
					valueNode9 = document.createElement("LI");                 
					nodePrice9 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode9);
					document.getElementById("lista2").appendChild(node9);
					document.getElementById("valorU").appendChild(valueNode9);
					document.getElementById("lista3").appendChild(nodePrice9);
					itemNode9.innerHTML = $("#itm9").html();
					node9.innerHTML = count;
					valueNode9.innerHTML = Number($("#itm9").attr('data-value'));
					nodePrice9.innerHTML = Number($("#itm9").attr('data-value'))*count*dia9;
					selected8 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode9);
					document.getElementById("lista2").removeChild(node9);
					document.getElementById("valorU").removeChild(valueNode9);
					document.getElementById("lista3").removeChild(nodePrice9);
					selected8 = false;
				}
				else {
					node9.innerHTML = count;
					nodePrice9.innerHTML = Number($("#itm9").attr('data-value'))*count*dia9;
				}
				price[8] = +Number($("#itm9").attr('data-value'))*count*dia9;
			}

			if (id === "itemDias10") {
				dia10 = Number($("#dias10").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay10 == false) {
					diaNode10 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode10);
					diaNode10.innerHTML = Number($("#dias10").attr('data-value'))*Number(count);
					selectedDay10 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode10);
					selectedDay10 = false;
				}
				else {
					diaNode10.innerHTML = Number($("#dias10").attr('data-value'))*Number(count);
				}
				if (nodePrice10) {
					nodePrice10.innerHTML = Number($("#itm10").attr('data-value'))*dia10;
				}
				price[9] = +Number($("#itm10").attr('data-value'))*dia10;
			}
			if (id === "item10") {
				if (count == 1 && selected9 == false) {
					itemNode10 = document.createElement("LI");
					node10 = document.createElement("LI");
					valueNode10 = document.createElement("LI");                 
					nodePrice10 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode10);
					document.getElementById("lista2").appendChild(node10);
					document.getElementById("valorU").appendChild(valueNode10);
					document.getElementById("lista3").appendChild(nodePrice10);
					itemNode10.innerHTML = $("#itm10").html();
					node10.innerHTML = count;
					valueNode10.innerHTML = Number($("#itm10").attr('data-value'));
					nodePrice10.innerHTML = Number($("#itm10").attr('data-value'))*count*dia10;
					selected9 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode10);
					document.getElementById("lista2").removeChild(node10);
					document.getElementById("valorU").removeChild(valueNode10);
					document.getElementById("lista3").removeChild(nodePrice10);
					selected9 = false;
				}
				else {
					node10.innerHTML = count;
					nodePrice10.innerHTML = Number($("#itm10").attr('data-value'))*count*dia10;
				}
				price[9] = +Number($("#itm10").attr('data-value'))*count*dia10;
			}

			if (id === "itemDias11") {
				dia11 = Number($("#dias11").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay11 == false) {
				diaNode11 = document.createElement("LI");
				document.getElementById("diaList").appendChild(diaNode11);
				diaNode11.innerHTML = Number($("#dias11").attr('data-value'))*Number(count);
				selectedDay11 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode11);
					selectedDay11 = false;
				}
				else {
					diaNode11.innerHTML = Number($("#dias11").attr('data-value'))*Number(count);
				}
				if (nodePrice11) {
					nodePrice11.innerHTML = Number($("#itm11").attr('data-value'))*dia11;
				}
				price[10] = +Number($("#itm11").attr('data-value'))*dia11;
			}
			if (id === "item11") {
				if (count == 1 && selected10 == false) {
					itemNode11 = document.createElement("LI");
					node11 = document.createElement("LI");
					valueNode11 = document.createElement("LI");                 
					nodePrice11 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode11);
					document.getElementById("lista2").appendChild(node11);
					document.getElementById("valorU").appendChild(valueNode11);
					document.getElementById("lista3").appendChild(nodePrice11);
					itemNode11.innerHTML = $("#itm11").html();
					node11.innerHTML = count;
					valueNode11.innerHTML = Number($("#itm11").attr('data-value'));
					nodePrice11.innerHTML = Number($("#itm11").attr('data-value'))*count*dia11;
					selected10 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode11);
					document.getElementById("lista2").removeChild(node11);
					document.getElementById("valorU").removeChild(valueNode11);
					document.getElementById("lista3").removeChild(nodePrice11);
					selected10 = false;
				}
				else {
					node11.innerHTML = count;
					nodePrice11.innerHTML = Number($("#itm11").attr('data-value'))*count*dia11;
				}
				price[10] = +Number($("#itm11").attr('data-value'))*count*dia11;
			}

			if (id === "itemDias12") {
				dia12 = Number($("#dias12").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay12 == false) {
					diaNode12 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode12);
					diaNode12.innerHTML = Number($("#dias12").attr('data-value'))*Number(count);
					selectedDay12 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode12);
					selectedDay12 = false;
				}
				else {
					diaNode12.innerHTML = Number($("#dias12").attr('data-value'))*Number(count);
				}
				if (nodePrice12) {
					nodePrice12.innerHTML = Number($("#itm12").attr('data-value'))*dia12;
				}
				price[11] = +Number($("#itm12").attr('data-value'))*dia12;
			}
			if (id === "item12") {
				if (count == 1 && selected11 == false) {
					itemNode12 = document.createElement("LI");
					node12 = document.createElement("LI");
					valueNode12 = document.createElement("LI");                 
					nodePrice12 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode12);
					document.getElementById("lista2").appendChild(node12);
					document.getElementById("valorU").appendChild(valueNode12);
					document.getElementById("lista3").appendChild(nodePrice12);
					itemNode12.innerHTML = $("#itm12").html();
					node12.innerHTML = count;
					valueNode12.innerHTML = Number($("#itm12").attr('data-value'));
					nodePrice12.innerHTML = Number($("#itm12").attr('data-value'))*count*dia12;
					selected11 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode12);
					document.getElementById("lista2").removeChild(node12);
					document.getElementById("valorU").removeChild(valueNode12);
					document.getElementById("lista3").removeChild(nodePrice12);
					selected11 = false;
				}
				else {
					node12.innerHTML = count;
					nodePrice12.innerHTML = Number($("#itm12").attr('data-value'))*count*dia12;
				}
				price[11] = +Number($("#itm12").attr('data-value'))*count*dia12;
			}

			if (id === "itemDias13") {
				dia13 = Number($("#dias13").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay13 == false) {
					diaNode13 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode13);
					diaNode13.innerHTML = Number($("#dias13").attr('data-value'))*Number(count);
					selectedDay13 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode13);
					selectedDay13 = false;
				}
				else {
					diaNode13.innerHTML = Number($("#dias13").attr('data-value'))*Number(count);
				}
				if (nodePrice13) {
					nodePrice13.innerHTML = Number($("#itm13").attr('data-value'))*dia13;
				}
				price[12] = +Number($("#itm13").attr('data-value'))*dia13;
			}
			if (id === "item13") {
				if (count == 1 && selected12 == false) {
					itemNode13 = document.createElement("LI");
					node13 = document.createElement("LI");
					valueNode13 = document.createElement("LI");                 
					nodePrice13 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode13);
					document.getElementById("lista2").appendChild(node13);
					document.getElementById("valorU").appendChild(valueNode13);
					document.getElementById("lista3").appendChild(nodePrice13);
					itemNode13.innerHTML = $("#itm13").html();
					node13.innerHTML = count;
					valueNode13.innerHTML = Number($("#itm13").attr('data-value'));
					nodePrice13.innerHTML = Number($("#itm13").attr('data-value'))*count*dia13;
					selected12 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode13);
					document.getElementById("lista2").removeChild(node13);
					document.getElementById("valorU").removeChild(valueNode13);
					document.getElementById("lista3").removeChild(nodePrice13);
					selected12 = false;
				}
				else {
					node13.innerHTML = count;
					nodePrice13.innerHTML = Number($("#itm13").attr('data-value'))*count*dia13;
				}
				price[12] = +Number($("#itm13").attr('data-value'))*count*dia13;
			}

			if (id === "itemDias14") {
				dia14 = Number($("#dias14").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay14 == false) {
					diaNode14 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode14);
					diaNode14.innerHTML = Number($("#dias14").attr('data-value'))*Number(count);
					selectedDay14 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode14);
					selectedDay14 = false;
				}
				else {
					diaNode14.innerHTML = Number($("#dias14").attr('data-value'))*Number(count);
				}
				if (nodePrice14) {
					nodePrice14.innerHTML = Number($("#itm14").attr('data-value'))*dia14;
				}
				price[13] = +Number($("#itm14").attr('data-value'))*dia14;
			}
			if (id === "item14") {
				if (count == 1 && selected13 == false) {
					itemNode14 = document.createElement("LI");
					node14 = document.createElement("LI");
					valueNode14 = document.createElement("LI");                 
					nodePrice14 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode14);
					document.getElementById("lista2").appendChild(node14);
					document.getElementById("valorU").appendChild(valueNode14);
					document.getElementById("lista3").appendChild(nodePrice14);
					itemNode14.innerHTML = $("#itm14").html();
					node14.innerHTML = count;
					valueNode14.innerHTML = Number($("#itm14").attr('data-value'));
					nodePrice14.innerHTML = Number($("#itm14").attr('data-value'))*count*dia14;
					selected13 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode14);
					document.getElementById("lista2").removeChild(node14);
					document.getElementById("valorU").removeChild(valueNode14);
					document.getElementById("lista3").removeChild(nodePrice14);
					selected13 = false;
				}
				else {
					node14.innerHTML = count;
					nodePrice14.innerHTML = Number($("#itm14").attr('data-value'))*count*dia14;
				}
				price[13] = +Number($("#itm14").attr('data-value'))*count*dia14;
			}

			if (id === "itemDias15") {
				dia15 = Number($("#dias15").attr('data-value'))*Number(count);
				if (count == 1 & selectedDay15 == false) {
					diaNode15 = document.createElement("LI");
					document.getElementById("diaList").appendChild(diaNode15);
					diaNode15.innerHTML = Number($("#dias15").attr('data-value'))*Number(count);
					selectedDay15 = true;
				}
				else if (count == 0) {
					document.getElementById("diaList").removeChild(diaNode15);
					selectedDay15 = false;
				}
				else {
					diaNode15.innerHTML = Number($("#dias15").attr('data-value'))*Number(count);
				}
				if (nodePrice15) {
					nodePrice15.innerHTML = Number($("#itm15").attr('data-value'))*dia15;
				}
				price[14] = +Number($("#itm15").attr('data-value'))*dia15;
			}
			if (id === "item15") {
				if (count == 1 && selected14 == false) {
					itemNode15 = document.createElement("LI");
					node15 = document.createElement("LI");
					valueNode15 = document.createElement("LI");
					nodePrice15 = document.createElement("LI");
					document.getElementById("lista").appendChild(itemNode15);                 
					document.getElementById("lista2").appendChild(node15);
					document.getElementById("valorU").appendChild(valueNode15);
					document.getElementById("lista3").appendChild(nodePrice15);
					itemNode15.innerHTML = $("#itm15").html();
					node15.innerHTML = count;
					valueNode15.innerHTML = Number($("#itm15").attr('data-value'));
					nodePrice15.innerHTML = Number($("#itm15").attr('data-value'))*count*dia15;
					selected14 = true;
				}
				else if (count == 0) {
					document.getElementById("lista").removeChild(itemNode15);
					document.getElementById("lista2").removeChild(node15);
					document.getElementById("valorU").removeChild(valueNode15);
					document.getElementById("lista3").removeChild(nodePrice15);
					selected14 = false;
				}
				else {
					node15.innerHTML = count;
					nodePrice15.innerHTML = Number($("#itm15").attr('data-value'))*count*dia15;
				}
				price[14] = +Number($("#itm15").attr('data-value'))*count*dia15;
			}

			function getSum(total, num) {
				return total + num;
			}

			function myFunction(item) {
				$("#subtotal").html(price.reduce(getSum, 0)); 
				$("#price").html(price.reduce(getSum, 0)+((price.reduce(getSum, 0)/100)*30));
			}

			myFunction();

		}
  			
  	});
  				
//--------------------------------------------------------------------------------------------
	  
   $("#sender").on("click",function(){ 
   		alert("Tu cotización está siendo generada y se descargará automáticamente");
   		document.getElementsByClassName('pdfFill')[0].style.top = "0px";
   		document.getElementsByClassName('pdfFill')[0].style.position = "absolute";

   		if (displayElement === false) {
			document.getElementsByClassName('pdfFill')[0].style.display = "block";
			document.getElementsByClassName('pdfFill')[0].scrollIntoView();
			displayElement = true;	
   		}
   		
   		if (stateBool === false) {
   			document.getElementById("fechaNo").innerHTML = document.getElementById("fechaCot").value;
			document.getElementById("cotizacionNo").innerHTML = document.getElementById("numeroCot").value;
   			document.getElementById("EmpresaPDF").innerHTML = document.getElementById("negocio").value;
			document.getElementById("ContactoPDF").innerHTML = document.getElementById("contacto").value;
			document.getElementById("CelularPDF").innerHTML = document.getElementById("phone").value;
			document.getElementById("CargoPDF").innerHTML = document.getElementById("cargo").value;
			document.getElementById("CiudadPDF").innerHTML = document.getElementById("city").value;
			document.getElementById("CorreoPDF").innerHTML = document.getElementById("email").value;
			document.getElementById("FechaEventoPDF").innerHTML = document.getElementById("fecha").value;
			document.getElementById("HoraInicioPDF").innerHTML = document.getElementById("horaInicio").value;
			document.getElementById("LugarEventoPDF").innerHTML = document.getElementById("lugar").value;
			document.getElementById("HoraFinPDF").innerHTML = document.getElementById("horaFin").value;
			document.getElementById("AforoEventoPDF").innerHTML = document.getElementById("aforo").value;
			document.getElementById("CiudadEventoPDF").innerHTML = document.getElementById("cityEvento").value;
			document.getElementById("DescripcionEventoPDF").innerHTML = document.getElementById("descripcion").value;
			document.getElementById("ListaPDF").innerHTML = document.getElementById("lista").innerHTML;
			document.getElementById("ListaPDF2").innerHTML = document.getElementById("lista2").innerHTML;
			document.getElementById("ListaDiasPDF").innerHTML = document.getElementById("diaList").innerHTML;
			document.getElementById("ValorUPDF").innerHTML = document.getElementById("valorU").innerHTML;
			document.getElementById("ListaPDF3").innerHTML = document.getElementById("lista3").innerHTML;
			document.getElementById("NombreResponsablePDF").innerHTML = document.getElementById("contacto").value;
			document.getElementById("TelefonoResponsablePDF").innerHTML = document.getElementById("phone").value;
			document.getElementById("CargoResponsablePDF").innerHTML = document.getElementById("cargo").value;
			document.getElementById("SubtotalPDF").innerHTML = document.getElementById("subtotal").innerHTML;
			document.getElementById("HonorarioPDF").innerHTML = Number((Number(document.getElementById("price").innerHTML)/100)*12);;
			document.getElementById("totalPDF").innerHTML = document.getElementById("price").innerHTML;
			stateBool = true;
   		}
		
   		if (stateBool == true) {
   			html2canvas(document.querySelector("#pdfToDownload"),{
   				useCORS: true,
   				allowTaint: true,
				windowWidth: document.querySelector("#pdfToDownload").offsetWidth,//scrollWidth
				windowHeight: document.querySelector("#pdfToDownload").offsetHeight//scrollHeight
			}).then(canvas => {
				var dataURL = canvas.toDataURL('image/png', 1.0);
				if(canvas.width > canvas.height){
					var doc = new jsPDF('l', 'mm', [canvas.width, canvas.height]);
				}
				else {
					var doc = new jsPDF('p', 'mm', [canvas.height, canvas.width]);
				}
				//var doc = new jsPDF("portrait","mm","tabloid");
				var width = doc.internal.pageSize.getWidth;
				var height = doc.internal.pageSize.getHeight;
				doc.addImage(dataURL,'PNG',10, 10, Number(width), Number(height)); //addImage(image, format, x-coordinate, y-coordinate, width, height) 270 250
				doc.save("cotizacion.pdf");
				});
			
			stateBool = false;
   		}

   		if (displayElement === true && stateBool === false) {
			document.getElementsByClassName('pdfFill')[0].style.display = "none";
			displayElement = false;	
   		}
   })
//--------------------------------------------------------------------------------------------------
	$("#cobroBtn").on("click",function(){ 
		alert("Tu cotización está siendo generada y se descargará automáticamente");
   		document.getElementsByClassName('pdfTercero')[0].style.top = "0px";
   		document.getElementsByClassName('pdfTercero')[0].style.position = "absolute";

   		if (displayElementTercero === false) {
			document.getElementsByClassName('pdfTercero')[0].style.display = "block";
			document.getElementsByClassName('pdfTercero')[0].scrollIntoView();
			displayElementTercero = true;	
   		}
   		
   		if (stateBoolTercero === false) {
   			document.getElementById("fechaNo").innerHTML = document.getElementById("fechaCot").value;
			document.getElementById("cotizacionNo").innerHTML = document.getElementById("numeroCot").value;
   			document.getElementById("cantidadTercero").innerHTML = document.getElementById("quanti").value;
			document.getElementById("totalTercero").innerHTML = document.getElementById("totalTercer").innerHTML;
			document.getElementById("EmpresaPDF").innerHTML = document.getElementById("negocio").value;
			document.getElementById("ContactoPDF").innerHTML = document.getElementById("contacto").value;
			document.getElementById("CelularPDF").innerHTML = document.getElementById("phone").value;
			document.getElementById("CargoPDF").innerHTML = document.getElementById("cargo").value;
			document.getElementById("CiudadPDF").innerHTML = document.getElementById("city").value;
			document.getElementById("CorreoPDF").innerHTML = document.getElementById("email").value;
			document.getElementById("FechaEventoPDF").innerHTML = document.getElementById("fecha").value;
			document.getElementById("HoraInicioPDF").innerHTML = document.getElementById("horaInicio").value;
			document.getElementById("LugarEventoPDF").innerHTML = document.getElementById("lugar").value;
			document.getElementById("HoraFinPDF").innerHTML = document.getElementById("horaFin").value;
			document.getElementById("AforoEventoPDF").innerHTML = document.getElementById("aforo").value;
			document.getElementById("CiudadEventoPDF").innerHTML = document.getElementById("cityEvento").value;
			document.getElementById("DescripcionEventoPDF").innerHTML = document.getElementById("descripcion").value;
			document.getElementById("NombreResponsablePDF").innerHTML = document.getElementById("contacto").value;
			document.getElementById("TelefonoResponsablePDF").innerHTML = document.getElementById("phone").value;
			document.getElementById("CargoResponsablePDF").innerHTML = document.getElementById("cargo").value;
			stateBoolTercero = true;
   		}
		
   		if (stateBoolTercero == true) {
   			html2canvas(document.querySelector("#pdfFillTercero"),{
   				useCORS: true,
   				allowTaint: true,
				windowWidth: document.querySelector("#pdfFillTercero").scrollWidth,
				windowHeight: document.querySelector("#pdfFillTercero").scrollHeight
			}).then(canvas => {
				var dataURLTercero = canvas.toDataURL('image/png', 1.0);
				if(canvas.width > canvas.height){
					var docTercero = new jsPDF('l', 'mm', [canvas.width, canvas.height]);
				}
				else {
					var docTercero = new jsPDF('p', 'mm', [canvas.height, canvas.width]);
				}
				var width = docTercero.internal.pageSize.getWidth;
				var height = docTercero.internal.pageSize.getHeight;
				docTercero.addImage(dataURLTercero,'PNG',10, 10, Number(width), Number(height)); //addImage(image, format, x-coordinate, y-coordinate, width, height) 270 250
				docTercero.save("pagoAtercero.pdf");
				});
			stateBoolTercero = false;
   		}

   		if (displayElementTercero === true && stateBoolTercero === false) {
			document.getElementsByClassName('pdfTercero')[0].style.display = "none";
			displayElementTercero = false;	
   		}
	})

	$("#quanti").on('input', function()  {
		document.getElementById("totalTercer").innerHTML = Number(Number(document.getElementById("quanti").value) + Number((Number(document.getElementById("quanti").value)/100)*15));
	});
});
